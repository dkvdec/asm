/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_labelinst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:46:22 by dheredat          #+#    #+#             */
/*   Updated: 2020/08/22 17:01:54 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int	is_label(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != LABEL_CHAR
		&& str[i] != '-' && str[i] != DIRECT_CHAR)
		i++;
	if (str[i] == LABEL_CHAR)
		return (i);
	else
		return (0);
}

int	is_correct_label(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != LABEL_CHAR)
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_inst(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i])
		return (check_opname(&str[i]));
	else
		return (0);
}
