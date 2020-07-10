/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wherearewe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 07:16:26 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/03 07:16:29 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char		*where_are_we(void)
{
	char	*where;

	where = (CTX(cur_direc)) ? ft_strdup(CTX(cur_direc)) : NULL;
	if (!where)
	{
		where = get_env("PWD",
			CTX(local_env) ? CTX(local_env) : CTX(env), CASE_TRUE);
		!where ? where = ft_get_pwd() : 0;
	}
	return (where);
}
