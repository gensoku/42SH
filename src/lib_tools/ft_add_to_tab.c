/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 23:55:40 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 00:24:07 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char		**ft_add_to_tab(char **array, char *add, char **add_tab)
{
	char	**ret;
	int		i;
	int		j;
	int		add_s;

	if (!array || (!add && !add_tab))
		return (NULL);
	i = -1;
	add_s = ft_len_tab(add_tab) + ft_len_tab(array);
	add_s += (add) ? 2 : 1;
	if (!(ret = (char **)ft_memalloc(sizeof(char *) * add_s)))
		return (NULL);
	while (array[++i])
		ret[i] = ft_strdup(array[i]);
	(add) ? ret[i] = ft_strdup(add) : 0;
	j = (add) ? i + 1 : i;
	i = 0;
	while (add_tab && add_tab[i])
	{
		ret[j] = ft_strdup(add_tab[i]);
		i++;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}
