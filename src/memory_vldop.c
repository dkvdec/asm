/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_vldop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:47:26 by dheredat          #+#    #+#             */
/*   Updated: 2020/08/22 17:02:38 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

t_vldop	*vldop_init(void)
{
	t_vldop	*op;
	int		i;

	if (!(op = (t_vldop *)malloc(sizeof(t_vldop))))
		return (NULL);
	i = -1;
	while (++i < LABELS)
		op->labels[i] = NULL;
	op->code = 0;
	ft_bzero(op->args, sizeof(int) * 3);
	op->arg1 = NULL;
	op->arg2 = NULL;
	op->arg3 = NULL;
	return (op);
}

void	vldop_del(t_vldop **op)
{
	int	i;

	if (op && *op)
	{
		i = 0;
		while (i < LABELS && (*op)->labels[i])
		{
			ft_strdel(&((*op)->labels[i]));
			i++;
		}
		ft_strdel(&((*op)->arg1));
		ft_strdel(&((*op)->arg2));
		ft_strdel(&((*op)->arg3));
		free(*op);
		*op = NULL;
	}
}
