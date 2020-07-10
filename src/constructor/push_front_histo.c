/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_front_histo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:33:25 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:11 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_histo		*push_front_histo(t_env *e, char *line2)
{
	t_histo		*node;
	t_histo		*tmp;
	char		*line;
	char		*tmp2;

	if (!line2 || ft_strlen(line2) == 0)
		return (NULL);
	line = NULL;
	tmp2 = ft_convert_space(line2, 0, 0, 0);
	line = ft_strtrim(tmp2);
	(tmp2) ? ft_memdel((void **)&tmp2) : 0;
	node = p_try(sizeof(t_histo), e);
	node->name = ft_strdup(line);
	(line) ? ft_memdel((void**)&line) : (void)line;
	if (!e->histo)
		return (node);
	else
	{
		tmp = e->histo;
		node->next = tmp;
		tmp->previous = node;
		e->histo = node;
	}
	return (node);
}
