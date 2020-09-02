/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:45:10 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/02 22:39:42 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
**							Описание p[5]
**		+ 0 - Имя
**		+ 1 - Комментарий чемпиона
**		+ 2 - Комментарий к коду
**		+ 3 - Начало метки
**		+ 4 - Инструкция
**		+ 5 - Пустая строка
*/

static int	tail_check(const char *tail)
{
	int	i;

	i = 0;
	while (tail[i] && (tail[i] == '\t' || tail[i] == ' '))
		i++;
	if (tail[i] && (tail[i] == COMMENT_CHAR || tail[i] == ALT_COMMENT_CHAR
											|| tail[i] == '\n'))
		return (1);
	else if (!tail[i])
		return (1);
	else
		return (0);
}

static char	*tail_search(char *str)
{
	while (*str != '"')
		str++;
	str++;
	while (*str != '"')
		str++;
	str++;
	return (str);
}

int			odnostrok(char *str, int len, int type)
{
	int	n;

	n = strrchr(&str[len], '"') - strchr(&str[len], '"') - 1;
	if (!tail_check(strrchr(&str[len], '"') + 1))
		quit(EN_TRASH, NULL, NULL);
	len = type ? COMMENT_LENGTH : PROG_NAME_LENGTH;
	if (n > len)
		quit(EN_NAMECHARS, NULL, NULL);
	return (type);
}

static void	mnogostrok_clean(char ***str, char *tmp, char *protail, char *tail)
{
	**str = tmp;
	ft_strdel(&tail);
	ft_strdel(&protail);
}

int			mnogostrok(char **str, int fd, int c)
{
	char	*protail;
	char	*tail;
	char	*tmp;
	int		e;

	if (c == 1)
	{
		if ((e = ft_read_until_ch(fd, '"', &protail)) < 0)
			ft_quit(e, '"');
		ft_read_until_ch(fd, '\n', &tail);
		(!tail_check(tail)) ? quit(EN_TRASH, NULL, NULL) : 0;
		(!(tmp = ft_strjoin(*str, protail))) ? quit(EN_MALLOC, NULL, NULL) : 0;
	}
	else
	{
		tail = tail_search(*str);
		(!tail_check(tail)) ? quit(EN_TRASH, NULL, NULL) : 0;
		tmp = ft_strchr(*str, '"');
		if (!(protail = ft_strnewncp(tmp, tail - tmp)))
			quit(EN_MALLOC, NULL, NULL);
		tmp = protail;
	}
	ft_strdel(str);
	mnogostrok_clean(&str, tmp, protail, tail);
	return (1);
}
