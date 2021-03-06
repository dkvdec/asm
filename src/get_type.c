/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:46:10 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/02 22:07:56 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
**							Описание p[5]
**		+ 0 - Имя
**		+ 1 - Комментарий чемпиона
**		+ 2 - пустая строка
**		+ 3 - Начало метки
**		+ 4 - Инструкция
*/

static int	is_name(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(NAME_CMD_STRING) &&
				str[i] && str[i] == NAME_CMD_STRING[i])
		i++;
	if (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '"'))
		return (0);
	return (i == ft_strlen(NAME_CMD_STRING) ? 1 : 0);
}

static int	is_comment(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(COMMENT_CMD_STRING) &&
				str[i] && str[i] == COMMENT_CMD_STRING[i])
		i++;
	if (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '"'))
		return (0);
	return (i == ft_strlen(COMMENT_CMD_STRING) ? 1 : 0);
}

static int	is_namecomm(char *str)
{
	if (is_name(str))
		return (0);
	else if (is_comment(str))
		return (1);
	else
		return (-1);
}

static int	is_labelinst(char *str)
{
	if (is_label(str))
		return (3);
	else if (is_inst(str) > 0)
		return (4);
	else
		return (-1);
}

int			get_type(char **str, int bytes, int fd, t_hero **hero)
{
	int		type;
	char	*s;

	if (!*str && bytes == -2)
		quit(EN_MALLOC, NULL, NULL);
	if (!(s = ft_str_white_trim(*str)))
	{
		ft_strdel(&s);
		return (2);
	}
	if ((ft_strlen(s) == 1 && *s == '\n')
	|| s[0] == COMMENT_CHAR || s[0] == ALT_COMMENT_CHAR)
	{
		ft_strdel(&s);
		ft_strdel(str);
		return (2);
	}
	ft_strdel(str);
	if (((type = is_namecomm(s)) != -1))
		if (check_namecomm(&s, type, fd, hero) >= 0)
			return (type);
	if ((type = is_labelinst(s)) > 0)
		return (parse_instruct(s, type, fd, hero));
	ft_strdel(&s);
	return (-1);
}
