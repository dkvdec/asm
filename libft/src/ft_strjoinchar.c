/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:38:16 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/01 23:48:25 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strjoinchar(char **str, char c)
{
	char	*tmp;
	size_t	len;

	if (!*str)
		return (0);
	len = ft_strlen(*str);
	if (!(tmp = (char *)malloc(sizeof(char) * (len + 2))))
		return (0);
	tmp = ft_strcpy(tmp, *str);
	if (len)
	{
		tmp[len] = c;
		tmp[len + 1] = 0;
	}
	else
	{
		tmp[0] = c;
		tmp[1] = 0;
	}
	ft_strdel(str);
	*str = tmp;
	return (1);
}
