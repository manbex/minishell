#include "minishell.h"

void	child(t_data *d, t_lst *l)
{
	if (check_builtins(l->cmd))
		execute_builtin(d, l);
	else
	{
		execve(l->cmd, l->arg, d->env);
	}
	exit_shell(d, EXIT_SUCCESS);
}

int	exe_cmd(t_data *d)
{
	t_lst	*tmp;

	if (!d->l)
		return (0);
	if (!d->l->next && check_builtins(d->l->cmd))
		return (execute_builtin(d, d->l), 0);
	tmp = d->l;
	while (tmp)
	{
		tmp->pid = fork();
		if (tmp->pid == 0)
			child(d, tmp);
		tmp = tmp->next;
	}
	tmp = d->l;
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	return (0);
}
