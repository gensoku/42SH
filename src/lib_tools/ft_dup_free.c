/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 05:37:54 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/30 05:37:55 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char		*ft_dup_free(char *to_free, char *to_dup)
{
	char	*ret;

	if (!to_dup)
		return (NULL);
	ret = ft_strdup(to_dup);
	if (to_free)
		free(to_free);
	return (ret);
}
