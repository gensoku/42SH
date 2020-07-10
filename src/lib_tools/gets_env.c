/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 11:32:35 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int		checkmatch(char *str, char *to_match, char *lower, char *upper)
{
	int			len;

	if (!str || !to_match)
		return (0);
	len = ft_strlen(to_match);
	if (!ft_strncmp(str, to_match, len))
		return (1);
	else if (lower && !ft_strncmp(str, lower, len))
		return (1);
	else if (upper && !ft_strncmp(str, upper, len))
		return (1);
	return (0);
}

static	char	*loop_match(char **env, char *str, char *lower, char *upper)
{
	int			i;
	char		*ret;
	char		*ret2;

	i = -1;
	ret = NULL;
	ret2 = NULL;
	while (env[++i])
	{
		if (env[i] && str && checkmatch(env[i], str, lower, upper))
		{
			if (ft_strlen_char(env[i], '=') == ft_strlen(str))
			{
				ret = ft_strdup(ft_strchr(env[i], '='));
				ret2 = (ret && ret[1]) ? ft_strdup(&ret[1]) : ft_strdup("");
				(ret) ? ft_memdel((void **)&ret) : 0;
				return (ret2);
			}
		}
	}
	ft_memdel((void**)&ret);
	return (NULL);
}

char			*get_env(char *str, char **env, int case_sensitive)
{
	int			i;
	char		*ret;
	char		*lower;
	char		*upper;

	ret = NULL;
	if (!env || !str)
		return (NULL);
	i = -1;
	lower = (case_sensitive) ? NULL : ft_strdup(str);
	upper = (case_sensitive) ? NULL : ft_strdup(str);
	ft_str_tolower(lower);
	ft_str_toupper(upper);
	ret = loop_match(env, str, lower, upper);
	ft_memdel((void **)&upper);
	ft_memdel((void **)&lower);
	return (ret);
}
