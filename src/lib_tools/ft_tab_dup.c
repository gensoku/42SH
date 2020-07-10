/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/21 23:55:03 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char		**ft_tab_dup(char **src)
{
	char	**dup;
	int		i;

	i = -1;
	if (!src || !*src)
		return (NULL);
	if (!(dup = (char **)ft_memalloc(sizeof(char *) * ft_len_tab(src) + 1)))
		return (NULL);
	while (src[++i])
		dup[i] = ft_strdup(src[i]);
	dup[i] = NULL;
	return (dup);
}
