/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_tool.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 04:16:07 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/10 04:16:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_comp	*norm_get_err(char *str, t_comp *list, t_tools *t, int opt)
{
	t_env	*e;

	e = get_e(NULL);
	if (opt)
		E_ERR = (str[1] && str[1] == ';') ? ft_strdup(E_SP) : ft_strdup(E_SS);
	else
		E_ERR = ft_strdup(E_SP);
	if (t)
		del_t_tools_(t);
	del_t_comp(list);
	return (NULL);
}
