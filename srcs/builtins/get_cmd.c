/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:57:18 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/12 02:46:20 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	check(char **env, t_builtins *data)
{
	if (ft_strchr(data->cmd_with_path[0], '/')
		&& find_cmd(data->cmd_with_path[0], env))
		return (printf("bash: %s: Is a directory\n", data->cmd_with_path[0]),
			0);
	else if (!ft_strcmp(data->cmd_with_path[0], ".")
		|| !ft_strcmp(data->cmd_with_path[0], ".."))
		return (printf("%s: command not found\n", data->cmd_with_path[0]), 0);
	return (0);
}*/

int	get_cmd(t_data *d)
{
	(void)d;
/*	t_builtins	data;

	data.cmd = d->l->arg;
	data.cmd_with_path = d->l->arg_path;
	check(d->env, &data);
	if (valid_input(&data, d) == FALSE)
		return (1);
	else if (valid_input(&data, d) == CUSTOM)
		return (execute_builtin(&data, d), 1);
	*/return (0);
}
