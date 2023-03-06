#include "minishell.h"

void	free_stuff(t_data *d)
{
	rl_clear_history();
	free(d->prompt);
	ft_lst_free(d->l);
	free(d->tmp);
}

void	exec_error(char *str, char **arg, t_data *d)
{
	int		error;
	struct stat	*buf;

	error = errno;
	if ((errno == 2 && !ft_strchr(str, '/')) || !ft_strcmp(str, ".") || !ft_strcmp(str, ".."))
		ft_fprintf(STDERR_FILENO, "minishell: %s: command not found\n", arg[0]);
	else if (error == 13)
	{
		buf = malloc(sizeof(struct stat));
		if (!buf)
			write(2, "Error when calling malloc\n", 26);
		else if (stat(str, buf) && errno != EACCES)
			write(STDERR_FILENO, "Error when calling stat\n", 24);
		else if (S_ISDIR(buf->st_mode))
			ft_fprintf(STDERR_FILENO, "minishell: %s: is a directory\n", str);
		else
			ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", str, strerror(error));
		free(buf);
	}
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", str, strerror(error));
	free(str);
	ft_free_tab(arg);
	free_garbage(&d->g);
	exit(EXIT_SUCCESS);
}
