#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochayche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/05 19:07:36 by ochayche          #+#    #+#              #
#    Updated: 2017/06/30 19:42:48 by vdoroshy         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SHELL = /bin/sh

LIB_DIR = ../inc/libft
PTF_DIR = ../inc/ft_printf
LIB = 	libft.a
PTF =	libftprintf.a

################################################################################
#	COREWAR
################################################################################
NAME = corewar

#********* -INC
INC_NAME =	corewar.h
INC_DIR =	inc
INC = $(addprefix $(INC_DIR)/, $(INC_NAME))
INC_OP = ../inc/op.h

#********* -OBJ
OBJ_DIR =	.obj
OBJ = $(subst .c,.o,$(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(SRC)))

#********* -SRC
SRC_DIR =	src
SRC = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
SRC_NAME =			main.c \
					asm_help_functions.c \
					both_asml.c \
					destruct.c \
					dump.c \
					exec_command.c \
					game.c \
					handling_args.c \
					init_data.c \
					lfork_fork_sti_st.c \
					live_add_sub_zjmp.c \
					lldi_ldi_lld_ld.c \
					or_xor_and_aff.c \
					proc_list.c \
					read_args.c \
					read_player1.c \
					read_player2.c \
					read_player3.c \
					shift_pc_on_map.c \
					sort_players.c \
					sort_list.c \
					visual_main.c \
					visual_init_destroy.c \
					visual_print_border.c \
					visual_key_event.c \
					visual_print_info.c \
					visual_print_proportion.c 
# add .c file ---->

################################################################################
#	RULES
################################################################################

.PHONY: all clean fclean re

all: $(LIB) $(PTF) $(NAME)

$(NAME): $(OBJ) $(INC) $(INC_OP)
	$(CC) $(CFLAGS) -I./inc/ $(OBJ) -L./$(PTF_DIR) -lftprintf -L./$(LIB_DIR) -lft -lcurses -o $(NAME)
	@echo "\033[33m'$(NAME)' compiling done.\033[0m"

$(LIB):
	@make -C $(LIB_DIR)

$(PTF):
	@make -C $(PTF_DIR)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -I./inc/ -c $(CFLAGS) $? -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIB_DIR)/ clean
	make -C $(PTF_DIR)/ clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_DIR)/$(LIB)
	rm -f $(PTF_DIR)/$(PTF)

re: fclean all
