/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 23:30:08 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 23:18:32 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void		colour_bold(char c)
{
	if (c == 'r')
		write(2, "\033[1;31m", 8);
	else if (c == 'g')
		write(2, "\033[1;32m", 8);
	else if (c == 'y')
		write(2, "\033[1;33m", 8);
	else if (c == 'b')
		write(2, "\033[1;34m", 8);
	else if (c == 'm')
		write(2, "\033[1;35m", 8);
	else if (c == 'c')
		write(2, "\033[1;36m", 8);
	else if (c == 'w')
		write(2, "\033[0m", 5);
}

static void		colour_tall(char c)
{
	if (c == 'r')
		write(2, "\033[0;31m", 8);
	else if (c == 'g')
		write(2, "\033[0;32m", 8);
	else if (c == 'y')
		write(2, "\033[0;33m", 8);
	else if (c == 'b')
		write(2, "\033[0;34m", 8);
	else if (c == 'm')
		write(2, "\033[0;35m", 8);
	else if (c == 'c')
		write(2, "\033[0;36m", 8);
	else if (c == 'w')
		write(2, "\033[0m", 5);
}

static void		colour_on(char c, char s)
{
	if (s == '+')
	{
		colour_bold(c);
	}
	else if (s == '-')
	{
		colour_tall(c);
	}
}

static int		colour_check(char *str)
{
	char c;
	char s;

	c = *(str + 0);
	s = *(str + 1);
	if ((c == 'r' || c == 'g' || c == 'y'
	|| c == 'b' || c == 'm' || c == 'c'
	|| c == 'w') && (s == '+' || s == '-'))
	{
		return (1);
	}
	return (0);
}

void			error_func(char *clr, char *str)
{
	size_t len;

	if (clr && colour_check(clr))
		colour_on(clr[0], clr[1]);
	len = ft_strlen(str);
	write(2, str, len);
	write(2, "\033[0m", 5);
	write(2, "\n", 1);
	exit(1);
}
