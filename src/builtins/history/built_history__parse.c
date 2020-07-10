/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history__parse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:49:26 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 05:03:48 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char		*built_history__parse_extract(char **dest,
	char *buffer, char *start, char *end)
{
	char		*tmp;
	char		*extracted;

	tmp = buffer;
	if (!(tmp = ft_strstr(buffer, start)))
		return (NULL);
	buffer += ft_strlen(start);
	if (*end == '\0')
		while (*tmp)
			tmp++;
	else if (!(tmp = ft_strstr(buffer, end)) || tmp == buffer)
		return (NULL);
	extracted = ft_strnew(tmp - buffer);
	ft_strncpy(extracted, buffer, tmp - buffer);
	ft_memdel((void **)dest);
	*dest = extracted;
	return (tmp);
}

static char		*built_history__parse_data(char *entry_raw, t_hentries *entry)
{
	while (*entry_raw)
	{
		if (!(entry_raw = built_history__parse_extract(&entry->time,
			entry_raw, ": ", ":")))
			return (NULL);
		if (!(entry_raw = built_history__parse_extract(&entry->state,
			entry_raw, ":", ";")))
			return (NULL);
		if (!(entry_raw = built_history__parse_extract(&entry->cmd,
			entry_raw, ";", "")))
			return (NULL);
	}
	return ("END");
}

static char		*built_history__parse_entryend(char *buffer)
{
	char	*match;

	match = buffer;
	while ((match = ft_strchr(match, '\n')) != buffer)
	{
		if (*buffer && !match)
			return (NULL);
		if (*(match - 1) && *(match - 1) == '\\')
			match++;
		else
			return (match);
	}
	return (NULL);
}

static char		*built_history__parse_entry(char *buffer, t_hentries *entry)
{
	char	*entry_end;
	char	*entry_raw;

	if (!*buffer)
		return ("END");
	if ((entry_end = built_history__parse_entryend(buffer)))
	{
		entry_raw = ft_strnew(entry_end - buffer);
		ft_strncpy(entry_raw, buffer, entry_end - buffer);
		if (!built_history__parse_data(entry_raw, entry))
		{
			ft_memdel((void **)&entry_raw);
			return (NULL);
		}
		ft_memdel((void **)&entry_raw);
		return (++entry_end);
	}
	else
		return (NULL);
}

int				built_history__parse(t_history *history)
{
	char			*adr_buffer;
	t_hentries		*entry;
	int				index;

	index = 1;
	adr_buffer = history->raw;
	while (*adr_buffer)
	{
		entry = built_history__hentries_new();
		adr_buffer = built_history__parse_entry(adr_buffer, entry);
		if (adr_buffer == NULL)
			return (0);
		else
			built_history__hentries_add(history, entry);
		if (history->type == HISTORY_OFFSET)
		{
			if (index == history->offset && history->offset > 0)
				return (1);
		}
		index++;
	}
	return (1);
}
