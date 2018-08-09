/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 15:00:54 by piliegeo          #+#    #+#             */
/*   Updated: 2018/08/03 15:00:55 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		prompt_print(void)
{
	ft_printf("\033[3m\033[5m");
	ft_printf("{blue}||{eoc}||{red}||{eoc}\n");
	ft_printf("{blue}FR{eoc}AN{red}CE{eoc}\n");
	ft_printf("{blue}WI{eoc}NN{red}ER{eoc}\n");
	ft_printf("{blue}||{eoc}||{red}||{eoc}\033[0m > ");
}
