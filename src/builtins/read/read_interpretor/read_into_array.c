/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_into_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 05:04:42 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/28 05:04:43 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char	*read_array_id(char *arr, int id)
{
	char	*ret;
	char	*tmp_id;

	if (!arr)
		return (NULL);
	ret = ft_strnew(ft_strlen(arr) + 11);
	ft_strcat(ret, arr);
	ft_strcat(ret, "[");
	tmp_id = ft_itoa(id);
	ft_strcat(ret, tmp_id);
	ft_strcat(ret, "]");
	ft_memdel((void **)&tmp_id);
	return (ret);
}

static char	*read_set_array_line(char *array_id, char *value)
{
	char	*ret;

	if (!array_id)
		return (NULL);
	ret = ft_strnew(ft_strlen(array_id) + ft_strlen(value) + 2);
	ft_strcat(ret, array_id);
	ft_strcat(ret, "=");
	ft_strcat(ret, value);
	return (ret);
}

void		read_into_array(t_read *r)
{
	char	**splited_line;
	char	*tmp;
	char	*tmp2;
	int		i;

	splited_line = ft_strsplit(CTX(line), ' ');
	if (!splited_line)
		return ;
	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	while (splited_line[i])
	{
		if (!update_var((tmp = read_array_id(r->a_arr, i)),
			splited_line[i], CONTEXT))
			set_var_((tmp2 = read_set_array_line(tmp, splited_line[i])),
				LOC_VAR, VAR_NEUTRAL);
		ft_memdel((void **)&tmp);
		ft_memdel((void **)&tmp2);
		i++;
	}
	ft_del_tab(splited_line);
	splited_line = NULL;
}
