/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 09:53:59 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 06:14:51 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

unsigned long			opts_get_static(unsigned long value)
{
	static unsigned long opts = 0;

	if (value != OPT_WALL_MAX)
		opts = value;
	return (opts);
}

int						is_opt_set(unsigned long flags, char a)
{
	if (!flags || !ft_isalpha(a))
		return (0);
	if (flags & ASSIGN_BIT(VALUE_ALPHA_BIT(a)))
		return (1);
	return (0);
}

static void				ope_on_flag(unsigned long *flags, char *av,
	int i, int opts_flags)
{
	if (opts_flags & XOR_OPTS)
		*flags ^= ASSIGN_BIT(VALUE_ALPHA_BIT(av[i]));
	else if (opts_flags & SUPR_OPTS)
		*flags -= ASSIGN_BIT(VALUE_ALPHA_BIT(av[i]));
	else if (opts_flags & LAST_OPTS)
	{
		*flags = 0;
		*flags |= ASSIGN_BIT(VALUE_ALPHA_BIT(av[i]));
	}
	else
		*flags |= ASSIGN_BIT(VALUE_ALPHA_BIT(av[i]));
}

static int				reset_f_return(unsigned long *flags,
	unsigned long save)
{
	*flags = save;
	return (-1);
}

int						check_opts(char *av, char *opts,
	unsigned long *flags, int opts_flags)
{
	int					i;
	int					ret;
	unsigned	long	save;

	ret = 0;
	i = 1;
	if (!av || !ft_strlen(av) || !av[0] || av[0] != '-' || !opts)
		return (0);
	if (av[0] == '-' && (!av[1] || (av[1] == '-' && !av[2])))
		return (0);
	save = *flags;
	while (av && av[i])
	{
		if (!ft_isalpha(av[i]))
			return (reset_f_return(flags, save));
		if (!ft_strchr(opts, av[i]))
			return (reset_f_return(flags, save));
		ope_on_flag(flags, av, i, opts_flags);
		i++;
		ret++;
	}
	return (ret);
}
