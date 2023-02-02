/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:19:09 by mbenicho          #+#    #+#             */
/*   Updated: 2023/02/01 08:23:32 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define COLOR "\1\033[38;5;208m\2"
# define COLOR_RESET "\1\x1b[0m\2"
# define PROMPT "minishell > "

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdint.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include "built_ins.h"
# include "libft.h"

typedef struct s_tok
{
	char			*str;
	struct s_tok	*next;
}					t_tok;

typedef struct s_redir
{
	char			*str;	//nom du fichier / limiteur
	int				type;	//type de redirection 0 pour > ou < et 1 pour >> ou <<
}					t_redir;

typedef struct s_lst
{
	int				pid;		//pour stocker l'id du process
	char			*cmd;		//nom de la commande en gardant le path
	char			**arg;		//tableau d'arguments du type {cmd(sans path), arg1, arg2, ...,  NULL}
	t_redir			*infile;	//tableau de infile a ouvrir dans l'ordre
	t_redir			*outfile;	//tableau de outfile a ouvrir dans l'ordre
	struct s_lst	*next;
}					t_lst;

typedef struct s_data
{
	t_lst			*l;		//la liste des commandes apres le parsing
	char			*tmp;	
	char			**env;
}					t_data;

char				**free_tab(char **tab, int i);
void				ft_free_redir(t_redir *ptr);
char				**init_env(char **env);
int					parsing(t_data *d, char *str);
int					init_list(t_data *d, t_tok *t);
int					new_tok(t_tok **t, char *str, int j);
void				free_tok(t_tok *t);
int					ft_tok_size(t_tok *t);
void				tok_extract(t_tok **t, t_tok **dest, t_tok *elem);
void				ft_free_tab(char **tab);
void				exit_shell(t_data *d, int code);
void				ft_lst_add_back(t_lst **l, t_lst *new);
t_lst				*ft_lst_free(t_lst *l);
void				print_tab(char **tab);		//temp
int					ft_history(t_data *d, char **str);
int					init_arg(t_lst *new, t_tok *t);
void				print_redir(t_redir *tab);	//temp
int					init_redir(t_redir **tab, t_tok *t);

#endif
