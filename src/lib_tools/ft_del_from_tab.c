/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_from_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 00:06:02 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 04:58:25 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char		**ft_del_from_tab(char **array, char *to_del)
{
	char	**ret;
	int		i;
	int		j;

	if (!array)
		return (NULL);
	if (!to_del)
		return (ft_tab_dup(array));
	if (!(ret = (char **)ft_memalloc(sizeof(char *) * ft_len_tab(array))))
		return (NULL);
	i = 0;
	j = 0;
	while (array[i])
	{
		if (ft_strcmp(to_del, array[i]))
		{
			ret[j] = ft_strdup(array[i]);
			j++;
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}
