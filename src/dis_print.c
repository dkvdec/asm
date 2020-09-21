/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 00:28:36 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 22:31:28 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void			print_header_to_dst_file(t_dis *asm_code)
{
	ft_putstr_fd(".name		",asm_code->fd_dst);
	ft_putchar_fd('\"', asm_code->fd_dst);
	ft_putstr_fd(asm_code->name, asm_code->fd_dst);
	ft_putendl_fd("\"", asm_code->fd_dst);
	ft_putstr_fd(".comment	",asm_code->fd_dst);
	ft_putchar_fd('\"', asm_code->fd_dst);
	ft_putstr_fd(asm_code->comment, asm_code->fd_dst);
	ft_putendl_fd("\"\n", asm_code->fd_dst);
}

static void		print_op_name(int fd, int code)
{
	(code == 1) ? ft_putstr_fd("live ", fd) : 0;
	(code == 2) ? ft_putstr_fd("ld   ", fd) : 0;
	(code == 3) ? ft_putstr_fd("st   ", fd) : 0;
	(code == 4) ? ft_putstr_fd("add  ", fd) : 0;
	(code == 5) ? ft_putstr_fd("sub  ", fd) : 0;
	(code == 6) ? ft_putstr_fd("and  ", fd) : 0;
	(code == 7) ? ft_putstr_fd("or   ", fd) : 0;
	(code == 8) ? ft_putstr_fd("xor  ", fd) : 0;
	(code == 9) ? ft_putstr_fd("zjmp ", fd) : 0;
	(code == 10) ? ft_putstr_fd("ldi  ", fd) : 0;
	(code == 11) ? ft_putstr_fd("sti  ", fd) : 0;
	(code == 12) ? ft_putstr_fd("fork ", fd) : 0;
	(code == 13) ? ft_putstr_fd("lld  ", fd) : 0;
	(code == 14) ? ft_putstr_fd("lldi ", fd) : 0;
	(code == 15) ? ft_putstr_fd("lfork", fd) : 0;
	(code == 16) ? ft_putstr_fd("aff  ", fd) : 0;
}

// static void		print_op_arg(int fd)
// {
// }

void         print_asm_code_to_dst_file(t_dis *asm_code)
{
    t_op*	cur;
	int		i;

    cur = asm_code->opers;
    while (cur)
    {
        print_op_name(asm_code->fd_dst, cur->code);
		i = 0;
		while (i < 3 && cur->types[i] != 0)
		{
			if (cur->types[i] == T_DIR)
			{
				ft_putstr_fd(" %", asm_code->fd_dst);
				ft_putnbr_fd((int)cur->nargs[i], asm_code->fd_dst);
			}
			else if (cur->types[i] == T_IND)
			{
				ft_putchar_fd(' ', asm_code->fd_dst);
				ft_putnbr_fd((int)cur->nargs[i], asm_code->fd_dst);
			}
			else if (cur->types[i] == T_REG)
			{
				ft_putstr_fd(" r", asm_code->fd_dst);
				ft_putnbr_fd((int)cur->nargs[i], asm_code->fd_dst);
			}
			if (i < 2 && cur->types[i + 1] != 0)
				ft_putchar_fd(',', asm_code->fd_dst);
			i++;
		}
		ft_putchar_fd('\n', asm_code->fd_dst);
		cur = cur->next;
    }
}