/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_mng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 00:31:57 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 23:21:55 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

t_dis		*init_dis_struct(char *file_name)
{
	t_dis *asm_code;

	if (!(asm_code = (t_dis *)malloc(sizeof(t_dis))))
		error_func("r-", "Error! Malloc error.");
	if ((asm_code->fd_src = open(file_name, O_RDONLY)) <= 0)
		error_func("r-", "Error! Src file open error.");
	asm_code->file_name = new_file_name(file_name, ".s");
	if ((asm_code->fd_dst = open(asm_code->file_name,
	O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR)) <= 0)
		error_func("r-", "Error! Dst file open error.");
	asm_code->name = NULL;
	asm_code->comment = NULL;
	asm_code->code_size = 0;
	asm_code->code = NULL;
	asm_code->pos = 0;
	asm_code->opers = NULL;
	return (asm_code);
}

void		add_oper(t_op **list, t_op *new)
{
	t_op *current;

	if (list)
	{
		if (*list)
		{
			current = *list;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		else
			*list = new;
	}
}

void		free_dis_struct(t_dis **asm_code)
{
	close((*asm_code)->fd_src);
	close((*asm_code)->fd_dst);
	ft_strdel(&((*asm_code)->file_name));
	ft_strdel(&((*asm_code)->name));
	ft_strdel(&((*asm_code)->comment));
	del_ops(((*asm_code))->opers);
	free((*asm_code)->code);
	free(*asm_code);
	*asm_code = NULL;
}
