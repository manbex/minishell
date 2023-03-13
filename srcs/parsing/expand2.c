#include "minishell.h"

int	separate_quotes(t_tok **t, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = parse_quotes(s + i);
		if (j)
			j++;
		if (j == 0)
		{
			while (s[i + j])
			{
				if (is_quotes(s, i, j))
					break ;
				j++;
			}
			if (j && new_tok(t, s + i, j))
				return (free_tok(*t), 1);
		}
		else if (j && new_tok(t, s + i, j))
			return (free_tok(*t), 1);
		i += j;
	}
	return (0);
}
