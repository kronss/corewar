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
CFLAGS = -I./inc/
# -Wall -Wextra -Werror
SHELL = /bin/sh


LIB_DIR = inc/libft/
PTF_DIR = inc/ft_printf/
LIB = 	libft.a
PTF =	libftprintf.a



################################################################################
#	ASM
################################################################################
NAME_ASM = skype

#********* -INC
INC_NAME_ASM =	corewar.h
INC_DIR_ASM =	inc
INC_ASM = $(addprefix $(INC_DIR_ASM)/, $(INC_NAME_ASM))

#********* -OBJ
OBJ_DIR_ASM =	./asm/.obj
OBJ_ASM = $(subst .c,.o,$(subst $(SRC_DIR_ASM)/,$(OBJ_DIR_ASM)/,$(SRC_ASM)))

#********* -SRC
SRC_DIR_ASM =	./asm/src
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
#	VM
################################################################################
NAME_VM = vvv

#********* -INC
INC_NAME_VM =	vm.h
INC_DIR_VM =	inc
INC_VM = $(addprefix $(INC_DIR_VM)/, $(INC_NAME_VM))

#********* -OBJ
OBJ_DIR_VM =	vm/.obj
OBJ_VM = $(subst .c,.o,$(subst $(SRC_DIR_VM)/,$(OBJ_DIR_VM)/,$(SRC_VM)))

#********* -SRC
SRC_DIR_VM =	vm/src
SRC_VM = $(addprefix $(SRC_DIR_VM)/, $(SRC_NAME_VM))
SRC_NAME_VM =			main.c \
						init_data.c \
						read_player.c \
						destruct.c
# add .c file ---->



################################################################################
#	RULES
################################################################################



all: $(LIB) $(PTF) $(NAME_ASM) $(NAME_VM)

$(NAME_ASM): $(OBJ_ASM) $(INC_ASM)
	@$(CC) $(CFLAGS) $(OBJ_ASM) -L./$(PTF_DIR) -lftprintf -L./$(LIB_DIR) -lft -o $(NAME_ASM)
	@printf "\033[33m\n'$(NAME_ASM)' compiling done.\n\033[0m"

$(NAME_VM): $(OBJ_VM) $(INC_VM)
	@$(CC) $(CFLAGS) $(OBJ_VM) -L./$(PTF_DIR) -lftprintf -L./$(LIB_DIR) -lft -o $(NAME_VM)
	@printf "\033[33m\n'$(NAME_VM)' compiling done.\n\033[0m"

$(LIB):


$(PTF):


$(OBJ_DIR_ASM)/%.o: $(SRC_DIR_ASM)/%.c | $(OBJ_DIR_ASM)
	@printf "\033[42m  \033[0m"
	$(CC) -c $(CFLAGS) $? -o $@

$(OBJ_DIR_ASM):
	@mkdir $(OBJ_DIR_ASM)

$(OBJ_DIR_VM)/%.o: $(SRC_DIR_VM)/%.c | $(OBJ_DIR_VM)
	@printf "\033[42m  \033[0m"
	$(CC) -c $(CFLAGS) $? -o $@

$(OBJ_DIR_VM):
	@mkdir $(OBJ_DIR_VM)

clean:
	@rm -rf $(OBJ_DIR_ASM)
	@rm -rf $(OBJ_DIR_VM)
	@echo "\033[31mСleaning completed\033[0m"



fclean: clean
	@rm -f $(NAME_ASM)
	@rm -f $(NAME_VM)
	@echo "\033[31mPrograms removed\033[0m"

re: fclean recg all

recg:
	@printf "\033[33mRecompiling...\n\033[0m"

t:
	./test/asm test/zork.s

tt: t
	xxd test/zork.cor


.PHONY: all clean fclean re recg t tt asm