/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:45:00 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/12 10:45:03 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

#define CHECK_BIT(var,pos)	(var & pos)
#define OPT_N 1
#define OPT_QUOTE 2
#define OPT_DOUBLE_QUOTE 4
#define BACKSPACE
#define CHARS "\\vtrfba"

int		ft_print_spec(char *ptr, int fd)
{
	int i;

	i = 0;
	if (ft_isdigit(ptr[2]) && ft_isdigit(ptr[3]) && ft_isdigit(ptr[4]))
	{
		i = (ptr[2] - 48) * 64;
		i += (ptr[3] - 48) * 8;
		i += (ptr[4] - 48);
		write(fd, &(i), 3);
		return (4);
	}
	else if (ft_isdigit(ptr[2]) && ft_isdigit(ptr[3]))
	{
		i += (ptr[3] - 48) * 8;
		i += (ptr[4] - 48);
		write(fd, &(i), 2);
		return (3);
	}
	else if (ft_isdigit(ptr[2]))
	{
		i += (ptr[4] - 48);
		write(fd, &(i), 1);
		return (2);
	}
	return (1);
}

int		printer_echo(int opt, char *ptr, int fd)
{
	--ptr;
	while (*(++ptr) != '\0')
		if (*ptr == '\"' && !(CHECK_BIT(opt, OPT_QUOTE)))
			opt |= OPT_DOUBLE_QUOTE;
		else if (*ptr == '\'' && !CHECK_BIT(opt, OPT_DOUBLE_QUOTE))
			opt |= OPT_QUOTE;
		else if (*ptr == '\\' && (!CHECK_BIT(opt, OPT_QUOTE)
				&& !CHECK_BIT(opt, OPT_DOUBLE_QUOTE)))
			;
		else if (*ptr == '\\' && (CHECK_BIT(opt, OPT_QUOTE)
				|| CHECK_BIT(opt, OPT_DOUBLE_QUOTE)))
		{
			if (ft_strchr(CHARS, ptr[1]) != NULL)
				ft_putchar_fd(ptr[1], fd);
			else if (ptr[1] == 'n' && !CHECK_BIT(opt, OPT_N))
				ft_putchar_fd('\n', fd);
			else if (ptr[1] == 'c')
				return (opt);
			++ptr;
		}
		else if (ptr[1] == '0')
			ptr = ptr + ft_print_spec(ptr, fd);
		else
			ft_putchar_fd(*ptr, fd);
	return (opt);
}

void	ft_echo_loop(int opt, char **ptr, int fd)
{
	while (*ptr)
	{
		opt = printer_echo(opt, *ptr, fd);
		ptr++;
		if (*ptr)
			ft_putchar_fd(' ', fd);
	}
	if (!CHECK_BIT(opt, OPT_N))
		ft_putchar_fd('\n', fd);
}

int		ft_option(char **option)
{
	int	opt;

	opt = 0;
	if (ft_strcmp(*option, "-n") == 0)
		opt |= OPT_N;
	else
		return (-1);
	return (opt);
}

void	ft_echo(char **argv, t_env *e)
{
	int		opt;
	int		i;
	char	**ptr;

	opt = 0;
	i = 0;
	(void)e;
	ptr = argv;
	if (ptr[1] && ptr[1][0] == '-')
	{
		if ((opt = ft_option(ptr + 1)) < 0)
		{
			e->last_status = 1;
			ft_putendl_fd("flag error", 2);
			return ;
		}
		ft_echo_loop(opt, ptr + 2, (e->fd[0] == -1) ? 1 : e->fd[0]);
	}
	else
		ft_echo_loop(0, ptr + 1, (e->fd[0] == -1) ? 1 : e->fd[0]);
	e->last_status = 0;
	return ;
}
