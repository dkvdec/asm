/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:34:04 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 22:46:59 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int				char_to_int(unsigned char *bytecode, size_t size)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	sign = (bytecode[0] & 0x80) ? -1 : 1;
	i = 0;
	while (size)
	{
		if (sign == -1)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign == -1)
		result = ~(result);
	return (result);
}

static int		get_4bytes(t_dis *asm_code)
{
	ssize_t			size;
	unsigned char	buffer[4];

	size = read(asm_code->fd_src, &buffer, 4);
	if (size == -1)
		error_func("r-", "Error! File read error.");
	if (size < 4)
		error_func("r-", "Error! Invalid file error.");
	return (char_to_int(buffer, 4));
}

static char		*get_str(t_dis *asm_code, size_t len)
{
	ssize_t	size;
	char	*buffer;

	if (!(buffer = ft_strnew(len)))
		error_func("r-", "Error! Malloc error.");
	size = read(asm_code->fd_src, buffer, len);
	if (size == -1)
		error_func("r-", "Error! File read error.");
	if (size < (ssize_t)len)
		error_func("r-", "Error! Invalid file error.");
	return (buffer);
}

unsigned char			*get_code(t_dis *asm_code)
{
	ssize_t	size;
	unsigned char	*buffer;
	char	byte;

	if (!(buffer = ft_memalloc(asm_code->code_size)))
		error_func("r-", "Error! Malloc error.");
	size = read(asm_code->fd_src, buffer, asm_code->code_size);
	if (size == -1)
		error_func("r-", "Error! File read error.");
	if (size < (ssize_t)asm_code->code_size ||
		read(asm_code->fd_src, &byte, 1) != 0)
		error_func("r-", "Error! Invalid file error.");
	return (buffer);
}

void			get_src_code(t_dis *asm_code)
{
	if (get_4bytes(asm_code) != COREWAR_EXEC_MAGIC)
		error_func("r-", "Error! Magic header check failed.");
	asm_code->name = get_str(asm_code, PROG_NAME_LENGTH);
	if (get_4bytes(asm_code) != 0)
		error_func("r-", "Error! Wrong file structure.");
	if ((asm_code->code_size = get_4bytes(asm_code)) < 0)
		error_func("r-", "Error! Invalid code size structure.");
	asm_code->comment = get_str(asm_code, COMMENT_LENGTH);
	if (get_4bytes(asm_code) != 0)
		error_func("r-", "Error! Wrong file structure.");
	asm_code->code = get_code(asm_code);
}
