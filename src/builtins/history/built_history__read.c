/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history__read.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:50:10 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 04:23:47 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int		built_history__read(t_history *history, int history_fd)
{
	struct stat		history_file;
	size_t			ret;
	char			*buffer;

	if (fstat(history_fd, &history_file) == -1)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (history_file.st_size + 1));
	ret = read(history_fd, buffer, history_file.st_size);
	buffer[ret] = 0;
	history->raw = buffer;
	return (1);
}
