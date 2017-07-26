#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochayche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/18 18:15:02 by ochayche          #+#    #+#              #
#    Updated: 2017/03/05 22:47:28 by ochayche         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS =  -Wall -Wextra -Werror -I./inc
SHELL = /bin/sh

LIB_DIR = ../inc/libft
PTF_DIR = ../inc/ft_printf
LIB = 	libft.a
PTF =	libftprintf.a

################################################################################
#	ASM
################################################################################
NAME_ASM = asm

#********* -INC
INC_NAME_ASM =	asm.h
INC_DIR_ASM =	inc
INC_ASM = $(addprefix $(INC_DIR_ASM)/, $(INC_NAME_ASM))
INC_OP = ../inc/op.h

#********* -OBJ
OBJ_DIR_ASM =	./.obj
OBJ_ASM = $(subst .c,.o,$(subst $(SRC_DIR_ASM)/,$(OBJ_DIR_ASM)/,$(SRC_ASM)))

#********* -SRC
SRC_DIR_ASM =	./src
SRC_ASM = $(addprefix $(SRC_DIR_ASM)/, $(SRC_NAME_ASM))
SRC_NAME_ASM =			asm_additionally.c \
						asm_body.c \
						asm_body_list.c \
						asm_error.c \
						asm_header.c \
						asm_main.c \
						asm_search.c \
						asm_args.c \
						asm_size.c \
						asm_write.c \
						disasm_file.c \
						disasm_header.c \
						disasm_args.c \
						both_asml.c
# add .c file ---->

################################################################################
#	RULES
################################################################################

.PHONY: all clean fclean re

all: $(LIB) $(PTF) $(NAME_ASM)

$(NAME_ASM): $(OBJ_ASM) $(INC_ASM) $(INC_OP)
	$(CC) $(CFLAGS) $(OBJ_ASM) -L./$(PTF_DIR) -lftprintf -L./$(LIB_DIR) -lft -o $(NAME_ASM)
	@echo "\033[33m'$(NAME_ASM)' compiling done.\033[0m"

$(LIB):
	@make -C $(LIB_DIR)

$(PTF):
	@make -C $(PTF_DIR)

$(OBJ_DIR_ASM)/%.o: $(SRC_DIR_ASM)/%.c | $(OBJ_DIR_ASM)
	$(CC) -c $(CFLAGS) $? -o $@

$(OBJ_DIR_ASM):
	mkdir $(OBJ_DIR_ASM)

clean:
	rm -rf $(OBJ_DIR_ASM)
	make -C $(LIB_DIR)/ clean
	make -C $(PTF_DIR)/ clean

fclean: clean
	rm -f $(NAME_ASM)
	rm -f $(LIB_DIR)/$(LIB)
	rm -f $(PTF_DIR)/$(PTF)

re: fclean all
