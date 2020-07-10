/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:59:15 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	display_error(int n, char *content, t_env *e)
{
	if (n == 0 && content)
		ft_putendl_fd(content, 2);
	else if (content)
	{
		ft_putendl_fd(content, 2);
		if (e)
			ft_exit(n, e, 0);
		else
			exit(-1);
	}
}
