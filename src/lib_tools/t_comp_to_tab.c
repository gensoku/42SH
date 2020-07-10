/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_comp_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:14 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char	**t_comp_to_tab(char **new, t_comp *list_elem)
{
	t_comp	*tmp;
	t_comp	*tmp2;
	int		i;

	i = 0;
	tmp = list_elem;
	tmp2 = tmp;
	while (tmp2)
	{
		new[i] = ft_strdup(tmp->name);
		ft_memdel((void **)&tmp->name);
		tmp2 = tmp2->next;
		ft_memdel((void **)&tmp);
		tmp = tmp2;
		i++;
	}
	new[i] = NULL;
	return (new);
}
