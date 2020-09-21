# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/22 14:42:42 by dheredat          #+#    #+#              #
#    Updated: 2020/09/21 23:54:02 by dheredat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS			=	-Wall -Wextra -Werror	
NAME			=	asm
LIBFT_DIR		=	libft
LIBFT_INC_DIR	=	$(LIBFT_DIR)/inc
INC_DIR			=	./inc
SRC_DIR			=	./src
OBJ_DIR			=	./obj
INC_ASM			=	$(INC_DIR)/asm.h $(INC_DIR)/op.h

SRC				=	args_checker.c\
					args_patterns.c\
					asm.c\
					asm_parser.c\
					byte_op.c\
					check_name.c\
					check_opname.c\
					converter.c\
					errors.c\
					ft_read_until_ch.c\
					get_type.c\
					is_labelinst.c\
					letter_check.c\
					memory_hero.c\
					memory_op.c\
					memory_vldop.c\
					operations.c\
					parse_inst.c\
					read_arguments.c\
					translator.c\
					error_func.c\
					dis_dec.c\
					dis_get.c\
					dis_mng.c\
					dis_type.c\
					dis_print.c


OBJS			=	$(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

LIBFT			=	$(LIBFT_DIR)/libft.a

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_ASM)
		@gcc $(FLAGS) -g -c $< -I$(INC_DIR) -I$(LIBFT_DIR)/inc -o $@ -MD
		@echo "\033[35mBuilding *.o\033[0m"

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS) $(INC_ASM)
		@echo "\033[1;32mBuilding asm\033[0m"
		@gcc -I $(LIBFT_INC_DIR) -I $(INC_DIR) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	@make -C libft

clean:
	@make -C libft clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm
