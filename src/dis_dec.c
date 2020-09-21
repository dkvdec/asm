/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_dec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 00:18:47 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 21:32:42 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static uint8_t	get_arg_type(int8_t code)
{
	if (code == DIR_CODE)
		return (T_DIR);
	else if (code == REG_CODE)
		return (T_REG);
	else if (code == IND_CODE)
		return (T_IND);
	else
		return (0);
}

static void		set_arg_type(int8_t arg_code,
								int8_t index,
								t_op *oper)
{
	oper->types[index] = get_arg_type(arg_code);
}

void			process_arg_types(t_dis *asm_code, t_op *oper)
{
	unsigned char args_types_code;

	if (oper->code != 1 && oper->code != 9 && oper->code != 12 && oper->code != 15)
	{
		args_types_code = asm_code->code[asm_code->pos];
		set_arg_type((int8_t)((args_types_code & 0xC0) >> 6), 0, oper);
		if (oper->code != 16)
			set_arg_type((int8_t)((args_types_code & 0x30) >> 4), 1, oper);
		else
			oper->types[1] = 0;
		if ((oper->code >= 4 && oper->code <= 8)
			|| oper->code == 10 || oper->code == 11 || oper->code == 14)
			set_arg_type((int8_t)((args_types_code & 0xC) >> 2), 2, oper);
		else
			oper->types[2] = 0;
	}
	else
	{
		oper->types[0] = 2;
		oper->types[1] = 0;
		oper->types[2] = 0;
	}
}

static size_t		get_size(t_op *oper, unsigned i)
{
	if (oper->types[i] == T_REG)
		return (1);
	else if (oper->types[i] == T_IND)
		return (IND_SIZE);
	else
		return (get_dirsize(oper->code));
}

static void			process_arg(t_dis *asm_code,
								t_op *oper,
								unsigned i)
{
	size_t size;

	size = get_size(oper, i);
	if (asm_code->code_size - asm_code->pos >= (int32_t)size)
	{
		oper->nargs[i] = (long)char_to_int(&asm_code->code[asm_code->pos], size);
		asm_code->pos += size;
	}
	else
		error_func("r-", "Error! Argument lenght error.");
}

static void			process_args(t_dis *asm_code, t_op *oper)
{
	unsigned i;

	i = 0;
	while (i < 3)
	{
		oper->nargs[i] = 0;
		if (oper->types[i] != 0)
			process_arg(asm_code, oper, i);
		i++;
	}
}

t_op	*process_oper(t_dis *asm_code)
{
	t_op			*oper;
	unsigned char	op_code;

	oper = new_op();
	op_code = asm_code->code[asm_code->pos];
	if (op_code >= 0x01 && op_code <= 0x10)
	{
		asm_code->pos++;
		oper->code = op_code;
		process_arg_types(asm_code, oper);
		if (op_code != 1 && op_code != 9 && op_code != 12 && op_code != 15)
			asm_code->pos++;
		process_args(asm_code, oper);
		printf("> op_code=%d type0=%d type1=%d type2=%d arg0=%ld arg1=%ld arg2=%ld\n",
		op_code, oper->types[0], oper->types[1], oper->types[2],
		oper->nargs[0], oper->nargs[1], oper->nargs[2l]);
	}
	else
		error_func("r-", "Error! Unknown operation code.");
	return (oper);
}

// void				process_exec_code(t_dis *asm_code)
// {
// 	while (asm_code->pos < asm_code->code_size)
// 		add_oper(&(asm_code->opers), process_oper(asm_code));
// }
