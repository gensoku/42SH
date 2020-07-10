/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_tab_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 00:48:44 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 00:52:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	ft_put_tab_fd(char **array, int fd, char c)
{
	if (!array)
		return ;
	while (*array)
	{
		ft_putstr_fd(*array, fd);
		if (c)
			ft_putchar_fd(c, fd);
		array++;
	}
}
