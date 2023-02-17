/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 02:33:30 by julmuntz          #+#    #+#             */
/*   Updated: 2023/02/16 17:10:33 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_var(t_export *current, t_data *d, int found)
{
	current = d->x;
	if (!found)
	{
		while (current->next)
			current = current->next;
		current->next = (t_export *)malloc(sizeof(t_export));
		current->next->key = d->x->new_key;
		current->next->value = d->x->new_value;
		current->next->next = NULL;
	}
}

void	update_var(t_export *current, t_data *d, int *plus)
{
	char	*add;

	if (*plus == 1)
	{
		if (!current->value)
			add = ft_strdup(d->x->new_value);
		else
		{
			add = ft_strjoin(current->value, d->x->new_value);
			ft_strdel(&current->value);
		}
		current->value = add;
	}
	else if (ft_strchr(d->l->arg[1], '=')
		&& ft_strcmp(current->value, d->x->new_value))
	{
		ft_strdel(&current->value);
		current->value = d->x->new_value;
	}
}

static void	get_var2(t_data *d, t_lst *l, int *plus, int *i)
{
	if (l->arg[1] && l->arg[1][*i] == '=' && d->x->key && d->x->value)
	{
		d->x->new_key = ft_strndup(l->arg[1], *i - *plus);
		d->x->new_value = ft_strndup(l->arg[1] + *i + 1,
				ft_strlen(l->arg[1]) - *i - 1);
	}
	else if (l->arg[1] && l->arg[1][*i] == '=' && d->x->key && !d->x->value)
	{
		d->x->new_key = ft_strndup(l->arg[1], *i - *plus);
		d->x->new_value = NULL;
	}
	else if (l->arg[1])
	{
		d->x->new_key = ft_strdup(l->arg[1]);
		d->x->new_value = NULL;
	}
}

int	get_var(t_data *d, t_lst *l, int *plus)
{
	int	i;

	i = 0;
	while (l->arg[1][i] != '=' && l->arg[1][i])
	{
		if (l->arg[1][i] == '+')
			(*plus)++;
		i++;
	}
	if (*plus > 1)
		return (ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s\': not a valid identifier\n",
				l->arg[1]), 1);
	get_var2(d, l, plus, &i);
	return (0);
}
