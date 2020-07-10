/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:32:11 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/19 10:08:38 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char		*ft_convert_space(char *str, int i, int j, int k)
{
	char	*ret;

	if (!str)
		return (NULL);
	if (!(ret = (char *)ft_memalloc(sizeof(char) * ft_strlen(str) + 1)))
		display_error(-1, "Malloc failed, safety exit\n", CONTEXT);
	(void)j;
	(void)k;
	while (str[i])
	{
		ret[i] = (ft_isspace(str[i]) == 1) ? 32 : str[i];
		i++;
	}
	return (ret);
}
