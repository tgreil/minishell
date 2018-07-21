/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:31:13 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/21 15:38:33 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				error(char *prog, char *msg, char *cmd, int ret)
{
	ft_printf("!2!%s %s %s\n", prog, msg, cmd);
	return (ret);
}
