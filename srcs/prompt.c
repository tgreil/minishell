/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:50:40 by tgreil            #+#    #+#             */
/*   Updated: 2018/07/21 17:07:22 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		prompt_print(void)
{
	ft_printf("{blue}||{eoc}||{red}||{eoc}\n");
	ft_printf("{blue}FR{eoc}AN{red}CE{eoc}\n");
	ft_printf("{blue}WI{eoc}NN{red}ER{eoc}\n");
	ft_printf("{blue}||{eoc}||{red}||{eoc} >");
}
