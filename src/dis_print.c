/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 00:28:36 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 00:42:21 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void		print_header_to_dst_file(t_dis *asm_code)
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

void         print_asm_code_to_dst_file(t_dis *asm_code)
{
    t_oper  cur;

    cur = asm_code->opers;
    while (cur)
    {
        // print op_name
        // print all_args
    }
}