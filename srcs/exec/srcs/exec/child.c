#include "minishell.h"

void	child(t_data *d, t_lst *l)
{
	char	*str;
	char	**arg;
	int		error;

	error = 0;
	if (check_builtins(l->cmd))
	{
		execute_builtin(d, l);
		if (d->in != STDIN_FILENO)
			close(d->in);
		if (d->out != STDOUT_FILENO)
			close(d->out);
		exit_shell(d, EXIT_SUCCESS);
	}
	if (d->in != STDIN_FILENO)
	{
		close(0);
		error = dup2(d->in, 0);
		close(d->in);
	}
	if (d->out != STDOUT_FILENO)
	{
		close(1);
		error += dup2(d->out, 1);
		close(d->out);
	}
	if (error < 0)
		exit_shell(d, EXIT_FAILURE);
	str = ft_strdup(l->cmd);
	if (!str)
		exit_shell(d, EXIT_FAILURE);
	if (find_cmd(&str, d->env))
	{
		free(str);
		exit_shell(d, EXIT_FAILURE);
	}
	arg = l->arg;
	l->arg = NULL;
	free_stuff(d);
	d->env = update_env(d);
	execve(str, arg, d->env);
	exec_error(str, arg, d);
}
