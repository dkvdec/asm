/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:44:05 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/20 21:00:35 by dheredat         ###   ########.fr       */
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

void launch_asm(char *file_name)
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

// int read_n_compare(int fd, int sample)
// {
// 	char buff[4];
// 	int size;

// 	size = read(fd, buff, 4);
// 	if (size < 0)
// 		exit (1);
// }

t_dis	*init_dis_struct(char *file_name)
{
	t_dis *asm_code;

	if (!(asm_code = (t_dis *)malloc(sizeof(t_dis))))
		error_func("r-", "Error! Malloc error.");
	if ((asm_code->fd_src = open(file_name, O_RDONLY)) <= 0)
		error_func("r-", "Error! Src file open error.");
	asm_code->file_name = new_file_name(file_name, ".s");
	if ((asm_code->fd_dst = open(asm_code->file_name, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR))<= 0)
		error_func("r-", "Error! Dst file open error.");
	asm_code->name = NULL;
	asm_code->comment = NULL;
	asm_code->code_size = 0;
	asm_code->code = NULL;
	// asm_code->pos = 0;
	// asm_code->statements = NULL;
	return (asm_code);
}

void	free_dis_struct(t_dis **asm_code)
{
	close((*asm_code)->fd_src);
	close((*asm_code)->fd_dst);
	ft_strdel(&((*asm_code)->file_name));
	ft_strdel(&((*asm_code)->name));
	ft_strdel(&((*asm_code)->comment));
}

int		char_to_int(unsigned char *bytecode, size_t size)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	sign = (bytecode[0] & 0x80) ? -1: 1;
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
		result *= sign;
	return (result);
}

static int	get_4bytes(t_dis *asm_code)
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

char		*get_str(t_dis *asm_code, size_t len)
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

char	*get_code(t_dis *asm_code)
{
	ssize_t	size;
	char	*buffer;
	char	byte;

	if (!(buffer = ft_memalloc(asm_code->code_size)))
		error_func("r-", "Error! Malloc error.");
	size = read(asm_code->fd_src, buffer, asm_code->code_size);
	if (size == -1)
		error_func("r-", "Error! File read error.");
	if (size < (ssize_t)asm_code->code_size || read(asm_code->fd_src, &byte, 1) != 0)
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

void	print_header_to_dst_file(t_dis *asm_code)
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

void	launch_dis(char *file_name)
{
	t_dis	*asm_code;

	asm_code = init_dis_struct(file_name);
	get_src_code(asm_code);
	printf("%s\n%s\n%s\n\n%s\n", asm_code->file_name, asm_code->name, asm_code->comment, asm_code->code);//
	// convert excode
	print_header_to_dst_file(asm_code);
	ptint_asm_code_to_dst_file(asm_code);
	//message
	free_dis_struct(&asm_code);
}

void check_file_name(char *file_name)
{
	char 	*ext_pnt;

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
	check_file_name(av[ac-1]);
	return (0);
}
