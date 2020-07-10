/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 11:01:44 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:00:27 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

size_t				exe_len(t_env *e)
{
	size_t		len;
	t_spath		*sp_tmp;
	t_exe		*ex_tmp;

	if (!e->paths)
		return (0);
	sp_tmp = e->paths;
	len = 0;
	while (sp_tmp)
	{
		ex_tmp = sp_tmp->list;
		while (ex_tmp)
		{
			len++;
			ex_tmp = ex_tmp->next;
		}
		sp_tmp = sp_tmp->next;
	}
	return (len);
}

unsigned long		do_hash(char *full_name, size_t hash_size)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = (int)*full_name++))
		hash = ((hash << 5) + hash) + c;
	return (hash % hash_size);
}

static void			hlp_r_v(size_t *i, int *break_error)
{
	*break_error = 0;
	*i = 0;
}

static int			set_h(t_env *e, size_t len_max, size_t i, int break_error)
{
	t_spath		*sp_tmp;
	t_exe		*ex_tmp;

	sp_tmp = e->paths;
	while (sp_tmp)
	{
		ex_tmp = sp_tmp->list;
		while (ex_tmp)
		{
			i = (int)(do_hash(ex_tmp->name, e->hash_size));
			break_error = 0;
			while (i < len_max && e->hash[i] && e->hash[i]->name)
			{
				i++;
				(i == len_max && !break_error) ? hlp_r_v(&i, &break_error) : 0;
			}
			if (e->hash[i])
				return (-1);
			e->hash[i] = ex_tmp;
			ex_tmp = ex_tmp->next;
		}
		sp_tmp = sp_tmp->next;
	}
	return (0);
}

void				set_hash(t_env *e)
{
	(e->hash) ? ft_memdel((void**)&e->hash) : 0;
	if (!e->paths)
		return ;
	e->hash_size = exe_len(e) * 16;
	if (!(e->hash = ft_memalloc(sizeof(t_exe*) * e->hash_size * 16 + 1)))
		display_error(-1, "Malloc failed on hashtable, safety exit.", e);
	ft_bzero(e->hash, e->hash_size * 16 + 1);
	set_h(e, e->hash_size * 16, 0, 0);
}
