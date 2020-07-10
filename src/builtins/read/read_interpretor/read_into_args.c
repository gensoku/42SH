/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_into_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 05:04:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/28 05:04:51 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char	*read_full_var(char *key, char *value)
{
	char	*ret;

	if (!key)
		return (NULL);
	ret = ft_strnew(ft_strlen(key) + ft_strlen(value) + 2);
	ft_strcat(ret, key);
	ft_strcat(ret, "=");
	ft_strcat(ret, value);
	return (ret);
}

static int	upd_set_args(t_read *r, int j, int i, char **splited_line)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	if (r->args[j] && r->args[j + 1])
	{
		if (!update_var(r->args[j], splited_line[i], CONTEXT))
			set_var_((tmp = read_full_var(r->args[j],
				splited_line[i])), LOC_VAR, VAR_NEUTRAL);
		ft_memdel((void **)&tmp);
		return (1);
	}
	else if (r->args[j])
	{
		tmp2 = ft_implode(&splited_line[i], ' ');
		if (!update_var(r->args[j], tmp2, CONTEXT))
			set_var_((tmp = read_full_var(r->args[j],
				tmp2)), LOC_VAR, VAR_NEUTRAL);
		ft_memdel((void **)&tmp2);
		ft_memdel((void **)&tmp);
		return (1);
	}
	return (0);
}

void		read_into_args(t_read *r)
{
	char	**splited_line;
	int		i;
	int		j;

	splited_line = ft_strsplit(CTX(line), ' ');
	if (!splited_line)
		return ;
	i = 0;
	j = 0;
	while (splited_line[i])
	{
		if (upd_set_args(r, j, i, splited_line))
			j++;
		i++;
	}
	ft_del_tab(splited_line);
	splited_line = NULL;
}
