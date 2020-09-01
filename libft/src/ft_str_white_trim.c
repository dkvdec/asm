/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_white_trim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:38:12 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/01 23:48:33 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char(const char s)
{
	return ((s == ' ' || s == '\t') ? (1) : (0));
}

char		*ft_str_white_trim(const char *s)
{
	int		start;
	int		end;
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	start = 0;
	while (is_char(s[start]))
		start++;
	end = ft_strlen(s);
	if (!end)
		return (NULL);
	while (is_char(s[--end]) && end >= start)
		;
	res = ft_strnew(end - start + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (start <= end)
		res[++i] = s[start++];
	return (res);
}
