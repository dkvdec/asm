/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:44:05 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/21 23:31:15 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void	show_usage(char *name)
{
	write(1, "Usage: ", 8);
	write(1, name, ft_strlen(name));
	write(1, " <asm_code.s> or <byte_code.cor>\n", 34);
	exit(0);
}

void		launch_asm(char *file_name)
{
	t_hero	*hero;
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) <= 0)
		ft_quit(-1, 0);
	hero = init_hero();
	read_file(fd, &hero);
	close(fd);
	translator(hero, file_name);
	del_hero(&hero);
}

void		launch_dis(char *file_name)
{
	t_dis	*asm_code;

	asm_code = init_dis_struct(file_name);
	get_src_code(asm_code);
	while (asm_code->pos < asm_code->code_size)
		add_oper(&(asm_code->opers), get_oper(asm_code));
	print_header_to_dst_file(asm_code);
	print_asm_code_to_dst_file(asm_code);
	free_dis_struct(&asm_code);
}

void		check_file_name(char *file_name)
{
	char	*ext_pnt;

	ext_pnt = NULL;
	ext_pnt = ft_strrchr(file_name, '.');
	if (ext_pnt == NULL)
		error_func("r-", "Error! No file exension found.");
	if (!(ft_strcmp(ext_pnt, ".s")))
		launch_asm(file_name);
	else if (!(ft_strcmp(ext_pnt, ".cor")))
		launch_dis(file_name);
	else
		error_func("r-", "Error! Invalid file exension found.");
}

int			main(int ac, char **av)
{
	if (ac == 1)
		show_usage(av[0]);
	check_file_name(av[ac - 1]);
	return (0);
}
