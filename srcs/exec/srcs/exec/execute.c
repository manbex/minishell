/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:27:16 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/02 00:56:10 by julmuntz         ###   ########.fr       */
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
			return (0);
		execute_builtin(d, d->l);
	}
	return (0);
}

static int	wait_childs(t_data *d)
{
	t_lst	*tmp;

	tmp = d->l;
	while (tmp)
	{
		if (tmp->called)
			waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	return (0);
}

static void	open_pipes(t_data *d, t_lst *tmp, int *pipe_err, int *error)
{
	if (tmp == d->l)
		d->in = STDIN_FILENO;
	else
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
	if (!pipe_err && redirect(d, tmp))
		*error = 1;
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
	tmp = d->l;
	while (tmp)
	{
		error = 0;
		open_pipes(d, tmp, &pipe_err, &error);
		if (!pipe_err && !error && tmp->cmd)
			tmp->pid = fork();
		if (!pipe_err && !error && tmp->cmd && tmp->pid == 0)
		{
			if (tmp->next)
				close(d->pipe);
			child(d, tmp);
		}
		if (!pipe_err && !error && tmp->cmd && tmp->pid == -1)
			ft_fprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		else
			tmp->called = 1;
		if (d->heredoc)
		{
			d->heredoc = 0;
			unlink(".heredoc.tmp");
		}
		if (d->in != STDIN_FILENO)
			close(d->in);
		if (d->out != STDOUT_FILENO)
			close(d->out);
		tmp = tmp->next;
	}
	wait_childs(d);
	return (0);
}
