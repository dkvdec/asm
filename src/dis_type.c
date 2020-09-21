/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 23:28:34 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 23:47:22 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static unsigned char	get_darg_type(char code)
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

static void		set_darg_type(char arg_code,
								int i,
								t_op *oper)
{
	oper->types[i] = get_darg_type(arg_code);
}

void			get_darg_types(t_dis *asm_code, t_op *oper)
{
	unsigned char args_types_code;

	if (oper->code != 1 && oper->code != 9
		&& oper->code != 12 && oper->code != 15)
	{
		args_types_code = asm_code->code[asm_code->pos];
		set_darg_type((char)((args_types_code & 0xC0) >> 6), 0, oper);
		if (oper->code != 16)
			set_darg_type((char)((args_types_code & 0x30) >> 4), 1, oper);
		else
			oper->types[1] = 0;
		if ((oper->code >= 4 && oper->code <= 8)
			|| oper->code == 10 || oper->code == 11 || oper->code == 14)
			set_darg_type((char)((args_types_code & 0xC) >> 2), 2, oper);
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
