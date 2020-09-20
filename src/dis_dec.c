/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_dec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 00:18:47 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 01:31:12 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static size_t		get_size(t_op *statement, unsigned i)
{
	if (statement->args_types[i] == T_REG)
		return (1);
	else if (statement->args_types[i] == T_IND)
		return (IND_SIZE);
	else
		return (statement->op->t_dir_size);
}

static void			process_arg(t_dis *parser,
								t_op *statement,
								unsigned i)
{
	size_t size;

	size = get_size(statement, i);
	if (parser->code_size - parser->pos >= (int32_t)size)
	{
		statement->args[i] = bytecode_to_int32(&parser->code[parser->pos],
																		size);
		parser->pos += size;
		if (statement->args_types[i] == T_REG && statement->args[i] <= 0)
			register_error(parser);
	}
	else
		length_error(parser);
}

static void			process_args(t_dis *parser, t_op *statement)
{
	unsigned i;

	i = 0;
	while (i < statement->op->args_num)
	{
		process_arg(parser, statement, i);
		i++;
	}
}

static t_op	*process_statement(t_dis *parser)
{
	t_op	*statement;
	uint8_t		op_code;

	statement = init_op();
	op_code = parser->code[parser->pos];
	if (op_code >= 0x01 && op_code <= 0x10)
	{
		parser->pos++;
		statement->op = &g_op[INDEX(op_code)];
		if (statement->op->args_types_code && parser->pos >= parser->code_size)
			length_error(parser);
		process_arg_types(parser, statement);
		if (is_arg_types_valid(statement))
		{
			if (statement->op->args_types_code)
				parser->pos++;
			process_args(parser, statement);
		}
		else
			arg_types_code_error(parser);
	}
	else
		op_code_error(parser);
	return (statement);
}

void				process_exec_code(t_dis *parser)
{
	while (parser->pos < parser->code_size)
		add_statement(&(parser->statements), process_statement(parser));
}
