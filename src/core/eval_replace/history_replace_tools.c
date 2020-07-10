/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_replace_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:21:08 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/29 12:21:09 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		del_loc_entries(t_hentries *lst)
{
	t_hentries	*tmp;
	t_hentries	*tmp2;

	if (!lst)
		return ;
	tmp = lst;
	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_memdel((void **)&tmp->time);
		ft_memdel((void **)&tmp->state);
		ft_memdel((void **)&tmp->cmd);
		ft_memdel((void **)&tmp);
		tmp = tmp2;
	}
}

int				hist_setup_replace(int i, int k, char **line)
{
	t_history	struc;
	static char	*hist[3] = {"history", 0, 0};
	char		*tmp;
	char		*tmp2;

	ft_bzero((void *)&struc, sizeof(t_history));
	struc.type = 1;
	hist[1] = ft_strsub(*line, k + 1, i - k + 1);
	struc.offset = ft_atoi(hist[1]);
	if (struc.offset == 0)
	{
		ft_memdel((void **)&hist[1]);
		return (0);
	}
	tmp2 = built_history__replace(&struc, CONTEXT);
	tmp = tmp2 ? ft_str_sub_append(*line, tmp2, k, i - k + 1) : NULL;
	tmp ? ft_memdel((void **)line) : 0;
	ft_memdel((void **)&struc.raw);
	ft_memdel((void **)&tmp2);
	ft_memdel((void **)&hist[1]);
	del_loc_entries(struc.entries);
	tmp ? *line = tmp : 0;
	return (tmp ? 1 : 0);
}
