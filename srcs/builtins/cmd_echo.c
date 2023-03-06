/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:11:26 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/23 18:17:51 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start(char **arg, int n)
{
	int	i;
	int	c;

	i = n;
	while (arg[i] && !ft_strncmp(arg[i], "-n", 2))
	{
		c = 2;
		while (arg[i][c] == 'n')
			c++;
		if (!arg[i][c])
			i++;
		else
			break ;
	}
	return (i);
}

int	cmd_echo(t_data *d, t_lst *l)
{
	int	i;
	int	n;

	if (!l->arg[1])
		return (write(d->out, "\n", 1), 0);
	i = 1;
	n = 1;
	i = start(l->arg, n);
	if (l->arg[1])
	{
		while (l->arg[i])
		{
			ft_fprintf(d->out, "%s", l->arg[i]);
			if ((i) == (int)ft_arrstrlen(l->arg) - 1)
				break ;
			write(d->out, " ", 1);
			i++;
			n++;
		}
		if (n == i)
			write(d->out, "\n", 1);
	}
	return (0);
}
