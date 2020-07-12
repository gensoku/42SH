/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 06:47:37 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/19 10:04:36 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	sleep_du_pauvre(int n)
{
	int x;

	x = 0;
	while (n > 0 && x < n)
		x++;
}

char	*ft_get_file(char *path, int fd)
{
	char	*ret;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;

	ret = NULL;
	if (!path)
		return (ret);
	ft_bzero(&buff, BUFF_SIZE + 1);
	if ((fd = open(path, O_RDONLY, O_SYNC)) != -1)
	{
		while (read(fd, buff, BUFF_SIZE) > 0)
		{
			tmp = (ret) ? ft_strjoin(ret, buff) : ft_strdup(buff);
			(ret) ? free(ret) : 0;
			ret = ft_strdup(tmp);
			ft_memdel((void **)&tmp);
			ft_bzero(&buff, BUFF_SIZE);
		}
		close(fd);
	}
	(!ret) ? ret = ft_strdup("") : 0;
	return (ret);
}
