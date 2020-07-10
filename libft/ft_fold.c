/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fold.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 10:58:19 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/12 11:25:39 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_fold__gettotalmembers(t_foldm *members)
{
	int			index;

	index = 0;
	while (members && members->id)
	{
		members++;
		index++;
	}
	return (index);
}

static int		ft_fold__check(char *pattern, t_foldm *members)
{
	char		*tmp;
	int			index;

	index = 0;
	while (*pattern)
	{
		if (*pattern == '{')
		{
			while (*pattern != '}')
				pattern++;
			index++;
		}
		pattern++;
	}
	if (index == ft_fold__gettotalmembers(members))
		return (1);
	else
		return (0);
}

static char		*ft_fold__scan(char *pattern, t_foldm *members)
{
	char	*empty;
	char	*p_empty;
	int		total;

	total = 0;
	empty = ft_strnew(ft_strlen(pattern));
	p_empty = empty;
	while (*pattern)
	{
		if (*pattern == '{')
		{
			while (*pattern != '}')
				pattern++;
			pattern++;
		}
		*empty++ = *pattern++;
	}
	while (members && members->id)
	{
		total += ft_strlen((char *)members->data);
		members++;
	}
	total += ft_strlen(p_empty);
	ft_memdel((void **)&p_empty);
	return (ft_strnew(total));
}

static char		*ft_foldassign_f(char *stamp, char *pattern, t_foldm *members)
{
	char		*tmp;

	tmp = ft_strsub(stamp, 0, pattern - stamp);
	stamp = (char *)ft_foldassign(members, tmp, NULL)->data;
	ft_memdel((void **)&tmp);
	if (stamp)
		return (stamp);
	return (NULL);
}

char			*ft_fold(char *pattern, t_foldm *members)
{
	int				len;
	char			*folded;
	char			*b_folded;
	char			*stamp;

	if (!ft_fold__check(pattern, members))
		return (NULL);
	folded = ft_fold__scan(pattern, members);
	b_folded = folded;
	while (*pattern)
	{
		if (*pattern == '{')
		{
			stamp = ++pattern;
			while (*pattern != '}')
				pattern++;
			if (!(stamp = ft_foldassign_f(stamp, pattern, members)))
				return (NULL);
			ft_strcpy(folded, stamp);
			folded += ft_strlen(stamp);
			pattern++;
		}
		*folded++ = *pattern++;
	}
	return (b_folded);
}
