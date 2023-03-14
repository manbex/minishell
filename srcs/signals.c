/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:49:13 by julmuntz          #+#    #+#             */
/*   Updated: 2023/03/14 18:17:23 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = -3;
		rl_replace_line("", 0);
		rl_done = 1;
	}
}
