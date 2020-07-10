/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_quote_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:59:25 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	display_qu_error(int n)
{
	if (n == -1)
		ft_putendl_fd("parse error ')'", 2);
	if (n == -2)
		ft_putendl_fd("parse error ']'", 2);
	if (n == -3)
		ft_putendl_fd("parse error '}'", 2);
}
