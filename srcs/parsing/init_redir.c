#include "minishell.h"

int	init_redir(t_redir **tab, t_tok *t)
{
	int		size;
	int		i;
	t_tok	*tmp;

	if (t)
	{
		size = ft_tok_size(t) / 2;
		*tab = malloc((size + 1) * sizeof(t_redir));
		if (!*tab)
			return (free_tok(t), 1);
		i = 0;
		tmp = t;
		while (i < size)
		{
			(*tab)[i].type = 0;
			if (ft_strlen(tmp->str) == 2)
				(*tab)[i].type = 1;
			tmp = tmp->next;
			(*tab)[i].str = ft_strdup(tmp->str);
			if (!(*tab)->str)
				return (free_tok(t), ft_free_redir(*tab), *tab = NULL, 1);
			tmp = tmp->next;
			i++;
		}
		(*tab)[i].str = NULL;
	}
	return (free_tok(t), 0);
}
