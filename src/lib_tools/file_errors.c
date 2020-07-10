/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:01:35 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				set_ret_error(int n, char *name)
{
	char		*tmp;

	tmp = NULL;
	if (n == 2)
		ft_putendl_fd(tmp = ft_strjoin(name, ": is a CHR file"), 2);
	if (n == 3)
		ft_putendl_fd(tmp = ft_strjoin(name, ": is a directory"), 2);
	if (n == 4)
		ft_putendl_fd(tmp = ft_strjoin(name, ": is a FIFO file"), 2);
	if (n == 5)
		ft_putendl_fd(tmp = ft_strjoin(name, ": is a sym link"), 2);
	if (n == 1)
		ft_putendl_fd(tmp = ft_strjoin(name, ": is a block file"), 2);
	if (n == 7)
		ft_putendl_fd(tmp = ft_strjoin(name, ": is a socket"), 2);
	if (tmp)
		ft_memdel((void**)&tmp);
	return (-1);
}
