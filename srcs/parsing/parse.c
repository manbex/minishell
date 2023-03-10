/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:46 by mbenicho          #+#    #+#             */
/*   Updated: 2023/03/12 20:18:04 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_check(t_tok *t)
{
	if (!ft_strcmp(t->str, "|"))
		return (1);
	while (t)
	{
		if (((*(t->str) == '>' || *(t->str) == '<') && (!t->next \
		|| *(t->next->str) == '>' || *(t->next->str) == '<' || \
		*(t->next->str) == '|')) || (*(t->str) == '|' && (!t->next || \
		(t->next && *(t->next->str) == '|'))))
			return (1);
		t = t->next;
	}
	return (0);
}

static int	is_meta(char *str)
{
	int	i;

	i = 0;
	if (*str == '|' || *str == '>' || *str == '<')
	{
		i = 1;
		if ((*str == '>' && *(str + 1) == '>') \
		|| (*str == '<' && *(str + 1) == '<'))
			i = 2;
	}
	return (i);
}

int	parse_quotes(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '"')
		while (str[i] && str[i] != '"')
			i++;
	else if (str[0] == '\'')
		while (str[i] && str[i] != '\'')
			i++;
	else
		return (0);
	if (str[i] == 0)
		i = 0;
	return (i);
}

static int	parse_line(t_tok **t, char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		j = is_meta(str + i);
		if (j == 0)
		{
			while (str[i + j] && !ft_isspace(str[i + j])
				&& !is_meta(str + i + j))
			{
				if (str[i + j] == '"' || str[i + j] == '\'')
					j += parse_quotes(str + i + j);
				j++;
			}
		}
		if (j && new_tok(t, str + i, j))
			return (free(str), free_tok(*t), 1);
		i += j;
	}
	return (0);
}

int	parsing(t_data *d, char *str)
{
	t_tok	*t;

	t = NULL;
	str = expand_vars(d, str);
	if (!str)
		return (ft_puterr("minishell: malloc failed\n"), 1);
	if (*str == 0)
		return (free(str), 0);
	d->in = STDIN_FILENO;
	d->out = STDOUT_FILENO;
	if (!str)
		return (ft_puterr("minishell: malloc failed\n"), 1);
	if (parse_line(&t, str))
		return (ft_puterr("minishell: malloc failed\n"), 1);
	free(str);
	if (syntax_check(t))
		return (g_exit_code = 2, free_tok(t),
			ft_puterr("minishell: syntax error\n"), 0);
	if (init_list(d, t))
		return (ft_puterr("minishell: malloc failed\n"), 1);
	return (0);
}
