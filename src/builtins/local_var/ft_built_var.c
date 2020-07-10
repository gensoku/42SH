/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 09:20:27 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/21 09:20:29 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				check_before_equal(char *str, char *to_check)
{
	int			i;

	i = -1;
	while (str[++i])
		if (ft_strchr(to_check, str[i]))
			return (1);
	return (0);
}

static int		check_err_v_b(char **array, int i)
{
	char		*cut;
	char		save;
	int			ret;

	if (!array || !array[i])
		return (1);
	if (!(cut = ft_strchr(array[i], '=')))
		return (1);
	ret = 0;
	save = cut[1];
	cut[1] = 0;
	if (check_before_equal(array[i], "\'\"\""))
		ret = 1;
	cut[1] = save;
	return (ret);
}

static void		v_b_assign(char **array, int i)
{
	char		*cut;
	char		save;
	char		*b_eq;
	t_loc_var	*tmp;
	static char	*arr[4] = {"setenv", 0, 0, 0};

	if (!array || !array[i])
		return ;
	cut = ft_strchr(array[i], '=');
	save = cut[0];
	cut[0] = 0;
	b_eq = ft_strdup(array[i]);
	cut[0] = save;
	if (!(update_var(b_eq, &cut[1], CONTEXT)))
		set_var_(array[i], LOC_VAR, VAR_NEUTRAL);
	else if ((tmp = get_var_ptr(CONTEXT, b_eq, CASE_TRUE)) &&
		tmp->type == ENV_VAR)
	{
		arr[1] = b_eq;
		arr[2] = ft_strdup(&cut[1]);
		ft_setenv(arr, CONTEXT);
		ft_memdel((void **)&arr[2]);
	}
	ft_memdel((void **)&b_eq);
}

int				ft_built_var(char **array, t_env *e)
{
	int			i;
	char		*implode;

	i = -1;
	implode = NULL;
	if (!array || !array[0])
		return ((e->last_status = 1));
	while (array[++i])
	{
		if (check_err_v_b(array, i))
		{
			implode = ft_implode(&array[i], ' ');
			adv_exec(e, array[i], &array[i], 1);
			if (!e->pipe_builtin && e->tmp_pgid)
			{
				wait_pgid(e->tmp_pgid, e, 0);
				resume_state(e, 1, NULL);
			}
			ft_memdel((void **)&implode);
			return (0);
		}
		v_b_assign(array, i);
	}
	return ((e->last_status = 0));
}
