/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:45:00 by dheredat          #+#    #+#             */
/*   Updated: 2020/09/19 17:41:12 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

long		atoli(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		++i;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		++i;
	}
	return (res * sign);
}

char	*new_file_name(char *fn, char *ext)
{
	int		name_len;
	int		ext_len;
	char	*new_name;
	int		i;

	ext_len = ft_strlen(ext);
	name_len = ft_strlen(fn) - ((ext_len == 4) ? 2 : 4);
	if (!(new_name = ft_strnew(name_len + ext_len)))
		exit(1); // malloc error
	i = 0;
	while (i < name_len + ext_len)
	{
		if (i < name_len)
			new_name[i] = fn[i];
		else
			new_name[i] = ext[i - name_len];
		i++;
	}
	return (new_name);
}

static void	normal_output(char *fn)
{
	write(1, "Writing output program to ", 27);
	write(1, fn, ft_strlen(fn));
	write(1, "\n", 1);
	ft_strdel(&fn);
}

void		write_filler(unsigned char *bc,\
				t_hero *hero, unsigned int s, char *fn)
{
	int		fd;

	bc[0] = 0;
	bc[1] = 234;
	bc[2] = 131;
	bc[3] = 243;
	ft_memccpy(bc + 4, hero->name, 0, PROG_NAME_LENGTH);
	ft_memccpy(bc + 140, hero->comment, 0, COMMENT_LENGTH);
	fn = new_file_name(fn, ".cor"); //just generate new *.cor name
	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
	write(fd, bc, 4);
	write(fd, bc + 4, 128);
	write(fd, bc + 132, 4);
	bc[136] = (unsigned int)s >> 24;
	bc[137] = (unsigned int)s >> 16;
	bc[138] = (unsigned int)s >> 8;
	bc[139] = s;
	write(fd, bc + 136, 4);
	write(fd, bc + 140, 2048);
	write(fd, bc + 2188, 4);
	write(fd, hero->excode, s);
	normal_output(fn);
}
