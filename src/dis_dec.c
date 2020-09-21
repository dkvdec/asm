/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_dec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 00:18:47 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 23:46:36 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static size_t		get_size(t_op *oper, unsigned i)
{
	if (oper->types[i] == T_REG)
		return (1);
	else if (oper->types[i] == T_IND)
		return (IND_SIZE);
	else
		return (get_dirsize(oper->code));
}

static void			get_darg(t_dis *asm_code,
								t_op *oper,
								unsigned i)
{
	size_t size;

	size = get_size(oper, i);
	if (asm_code->code_size - asm_code->pos >= (int32_t)size)
	{
		oper->nargs[i] = (long)char_to_int(&asm_code->code[asm_code->pos],
																	size);
		asm_code->pos += size;
	}
	else
		error_func("r-", "Error! Argument lenght error.");
}

static void			get_dargs(t_dis *asm_code, t_op *oper)
{
	unsigned i;

	i = 0;
	while (i < 3)
	{
		oper->nargs[i] = 0;
		if (oper->types[i] != 0)
			get_darg(asm_code, oper, i);
		i++;
	}
}

t_op				*get_oper(t_dis *asm_code)
{
	t_op			*oper;
	unsigned char	op_code;

	oper = new_op();
	op_code = asm_code->code[asm_code->pos];
	if (op_code >= 0x01 && op_code <= 0x10)
	{
		asm_code->pos++;
		oper->code = op_code;
		get_darg_types(asm_code, oper);
		if (op_code != 1 && op_code != 9 && op_code != 12 && op_code != 15)
			asm_code->pos++;
		get_dargs(asm_code, oper);
	}
	else
		error_func("r-", "Error! Unknown operation code.");
	return (oper);
}
