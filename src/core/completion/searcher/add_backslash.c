/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_backslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:49:15 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		check_slash__(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\\')
		return (1);
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (1);
	if (c == '|')
		return (1);
	if (c == '&')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == ';')
		return (1);
	return (0);
}

static	char	*norm_loop_add_(char *str, int i, int j, char *ret)
{
	while (str[++i])
	{
		if (check_slash__(str[i]) == 1)
		{
			ret[j] = '\\';
			j++;
		}
		ret[j] = str[i];
		j++;
	}
	ret[j] = 0;
	return (ret);
}

char			*add_backslash(char *str, int type, int i)
{
	int			add;
	int			j;
	char		*ret;
	t_env		*e;

	if (!str)
		return (NULL);
	i = -1;
	add = 0;
	j = 0;
	(void)type;
	ret = NULL;
	while (str[++i])
		if (check_slash__(str[i]) == 1)
			add++;
	i = -1;
	e = get_e(NULL);
	if ((ret = (char *)malloc(sizeof(char) * ft_strlen(str) + add + 1)) == NULL)
		display_error(-1, "Malloc failed char *, exit", e);
	ret = norm_loop_add_(str, i, j, ret);
	return (ret);
}
