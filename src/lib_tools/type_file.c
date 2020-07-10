/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:24 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int		typedefineargs(int n)
{
	int		i;

	i = 0;
	i = (S_ISBLK(n)) ? 1 : i;
	i = (S_ISCHR(n)) ? 2 : i;
	i = (S_ISDIR(n)) ? 3 : i;
	i = (S_ISFIFO(n)) ? 4 : i;
	i = (S_ISLNK(n)) ? 5 : i;
	i = (S_ISREG(n)) ? 6 : i;
	i = (S_ISSOCK(n)) ? 7 : i;
	return (i);
}
