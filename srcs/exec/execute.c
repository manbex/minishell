/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:27:16 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/09 20:22:57 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_builtins(t_data *d)
{
	int	err;

	if (!d->l->next && check_builtins(d->l->cmd))
	{
		err = redirect(d, d->l);
		if (d->heredoc)
		{
			d->heredoc = 0;
			unlink(".heredoc.tmp");
		}
		if (err)
			return (g_exit_code = 1, 1);
		execute_builtin(d, d->l);
		return (1);
	}
	return (0);
}

static int	wait_childs(t_data *d)
{
	t_lst	*tmp;
	int		wstatus;

	tmp = d->l;
	while (tmp)
	{
		if (tmp->called)
		{
			waitpid(tmp->pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				g_exit_code = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == 2)
					g_exit_code = 130;
			else if (WIFSIGNALED(wstatus))
			{
				ft_puterr("Segmentation fault (core dumped)\n");
				g_exit_code = 139;
			}
			else
				g_exit_code = 1;
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	open_pipes(t_data *d, t_lst *tmp, int *pipe_err, int *error)
{
	if (tmp == d->l)
		d->in = STDIN_FILENO;
	else if (!*pipe_err)
	{
		close(d->pipefd[1]);
		d->in = d->pipe;
	}
	if (tmp->next && !*pipe_err)
	{
		if (pipe(d->pipefd))
		{
			*pipe_err = 1;
			ft_fprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		}
		d->out = d->pipefd[1];
		d->pipe = d->pipefd[0];
	}
	else
		d->out = STDOUT_FILENO;
	if (!*pipe_err && redirect(d, tmp))
	{
		*error = 1;
		g_exit_code = 1;
	}
}

static void	call_childs(t_data *d, t_lst *tmp, int *pipe_err, int *error)
{
	if (!*pipe_err && !*error && tmp->cmd)
	{
		tmp->pid = fork();
		if (tmp->pid == 0)
		{
			if (tmp->next)
				close(d->pipe);
			child(d, tmp);
		}
		if (tmp->pid == -1)
			ft_fprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		else
			tmp->called = 1;
	}
	if (d->heredoc)
	{
		d->heredoc = 0;
		unlink(".heredoc.tmp");
	}
	if (d->in != STDIN_FILENO && d->in != -1)
		close(d->in);
	if (d->out != STDOUT_FILENO && d->out != -1)
		close(d->out);
}

int	exe_cmd(t_data *d)
{
	t_lst	*tmp;
	int		pipe_err;
	int		error;

	d->heredoc = 0;
	pipe_err = 0;
	if (!d->l)
		return (0);
	if (handle_builtins(d))
		return (0);
	signal(SIGINT, &handle_ctrl_c);
	tmp = d->l;
	while (tmp)
	{
		tmp->called = 0;
		error = 0;
		open_pipes(d, tmp, &pipe_err, &error);
		call_childs(d, tmp, &pipe_err, &error);
		tmp = tmp->next;
	}
	wait_childs(d);
	return (0);
}
