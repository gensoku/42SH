/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foldassign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 10:58:19 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/12 11:25:48 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_foldm		*ft_foldassign(t_foldm *members, char *id, void *data)
{
	if (!members || !id)
		return (NULL);
	while (members && members->id)
	{
		if (ft_strstr(id, members->id))
		{
			if (data)
				members->data = data;
			return (members);
		}
		members++;
	}
	return (NULL);
}
