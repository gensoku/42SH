/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 04:33:13 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:34:54 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	ft_print_jobs(int z)
{
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(z, 2);
	ft_putstr_fd("]", 2);
}

void	ft_print_last_blast(int last)
{
	if (last == 1)
		ft_putstr_fd("+ ", 2);
	else if (last == 0)
		ft_putstr_fd("- ", 2);
	else
		ft_putstr_fd("  ", 2);
}
