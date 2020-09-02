/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:45:20 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/02 22:41:32 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
**	Между инструкцией и аргументтами должен быть пробел/таб,
**	если первый аргумен - T_REG
*/

int	is_blank(char *str)
{
	char	*s;

	if (!(s = ft_str_white_trim(str)))
		return (1);
	if (ft_strlen(s) == 1 && *s == '\n')
	{
		ft_strdel(&s);
		return (1);
	}
	if (*s == COMMENT_CHAR || *s == ALT_COMMENT_CHAR)
	{
		ft_strdel(&s);
		return (1);
	}
	ft_strdel(&s);
	return (0);
}

int	sep_char(char c)
{
	if (c == '\t' || c == ' '
		|| c == SEPARATOR_CHAR || c == '\n' || c == COMMENT_CHAR
			|| c == ALT_COMMENT_CHAR)
		return (1);
	return (0);
}

int	need_char(char c)
{
	if (c == DIRECT_CHAR || c == '\t' || c == ' ' || c == '-')
		return (1);
	return (0);
}

int	check_opname(char *str)
{
	if (*str == 'a')
		return (a_check(str));
	else if (*str == 'f')
		return (fxoz_check(str));
	else if (*str == 'l')
		return (l_check(str));
	else if (*str == 'o')
		return (fxoz_check(str));
	else if (*str == 's')
		return (s_check(str));
	else if (*str == 'x')
		return (fxoz_check(str));
	else if (*str == 'z')
		return (fxoz_check(str));
	else
		return (-1);
}

int	check_namecomm(char **str, int type, int fd, t_hero **hero)
{
	size_t	len;
	int		count;

	len = type ? ft_strlen(COMMENT_CMD_STRING) : ft_strlen(NAME_CMD_STRING);
	if (ft_strlen((*str)) <= len || ((*str)[len] != '\t'
								&& (*str)[len] != ' ' && (*str)[len] != '"'))
		quit(EN_CHAMP, NULL, NULL);
	while ((*str)[len] == '\t' || (*str)[len] == ' ')
		len++;
	if ((*str)[len] == '"')
	{
		if ((count = ft_countch(&(*str)[len], '"')) == 2)
			odnostrok(*str, len, type);
		else
			mnogostrok(str, fd, count);
		fill_hero(type, str, hero);
		return (type);
	}
	else
		quit(EN_CHAMPMISS, NULL, NULL);
	return (-1);
}
