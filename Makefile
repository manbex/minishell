# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 17:17:08 by julmuntz          #+#    #+#              #
#    Updated: 2023/02/04 15:51:41 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC_DIR		=	srcs/
SRC 		=	main.c					\
				history.c				\
				$(addprefix parsing/,	\
				env.c					\
				tok_utils.c				\
				lst_utils.c				\
				tab_utils.c				\
				parse.c					\
				parse2.c				\
				init_arg.c				\
				init_redir.c			\
				expand.c				\
				ft_tok_join.c			\
				)						\
				$(addprefix builtins/,	\
				get_cmd.c				\
				check_input.c			\
				cmd_echo.c				\
				cmd_pwd.c				\
				cmd_env.c				\
				cmd_cd.c				\
				)						\
				$(addprefix libft/,		\
				ft_strcmp.c				\
				ft_strlcpy.c			\
				ft_strdup.c				\
				ft_strtrim.c			\
				ft_superatoi.c			\
				ft_strjoin.c			\
				ft_arrlen.c				\
				ft_free_lines.c			\
				ft_isspace.c			\
				ft_split.c				\
				ft_strchr.c				\
				ft_strnstr.c			\
				ft_substr.c				\
				ft_calloc.c				\
				ft_bzero.c				\
				ft_strlen.c				\
				ft_putstr.c				\
				ft_count_chars.c		\
				)

OBJ_DIR		=	obj/
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC			=	cc
CFLAGS		=	-Iincludes -g
RM			=	rm -f

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline

all:			$(NAME)

clean:
					$(RM) -r $(OBJ_DIR)

fclean:			clean
					$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
