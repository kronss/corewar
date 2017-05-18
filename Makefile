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

#********************************* common *************************************#
.PHONY: all clean fclean re asm_test asm corewar
CC = gcc
# FLAGS = -Wall -Wextra -Werror


LIB_PATH = libft
PTF_PATH = ft_printf

LIB = 	libft.a
PTF =	libftprintf.a
#******************************************************************************#





#********************************* asm ****************************************#
NAME_ASM = asm_test


SRC_PATH_ASM = asm_path/src
INC_PATH_ASM = asm_path/inc
OBJ_PATH_ASM = asm_path/obj



SRC_NAME_ASM = main_asm.c
INC_NAME_ASM = main_asm.h
OBJ_NAME_ASM = $(SRC_NAME_ASM:.c=.o)




SRC_ASM = $(addprefix $(SRC_PATH_ASM)/, $(SRC_NAME_ASM))
INC_ASM = $(addprefix $(INC_PATH_ASM)/, $(INC_NAME_ASM))
OBJ_ASM = $(addprefix $(OBJ_PATH_ASM)/, $(OBJ_NAME_ASM))
#******************************************************************************#




#********************************* corewar *************************************#
NAME_COR = corewar_test
SRC_PATH_COR = cor_path/src
INC_PATH_COR = cor_path/inc
OBJ_PATH_COR = cor_path/obj
SRC_NAME_COR = main_cor.c
INC_NAME_COR = main_cor.h
OBJ_NAME_COR = $(SRC_NAME_COR:.c=.o)
SRC_COR = $(addprefix $(SRC_PATH_COR)/, $(SRC_NAME_COR))
INC_COR = $(addprefix $(INC_PATH_COR)/, $(INC_NAME_COR))
OBJ_COR = $(addprefix $(OBJ_PATH_COR)/, $(OBJ_NAME_COR))
#******************************************************************************#


all: $(LIB) $(PTF) create $(NAME_ASM)
	
create:
	@mkdir -p $(OBJ_PATH_ASM)

$(NAME_ASM): $(OBJ_ASM)
	$(CC) -o $(NAME_ASM) $(FLAGS) $(OBJ_ASM) $(LIB_PATH)/$(LIB) $(PTF_PATH)/$(PTF)

$(LIB):
	@make -C $(LIB_PATH)/

$(PTF):
	@make -C $(PTF_PATH)/



$(OBJ_ASM): $(SRC_ASM)
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_ASM)

	make -C $(LIB_PATH)/ clean
	make -C $(PTF_PATH)/ clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIB_PATH)/$(LIB)
	rm -rf $(PTF_PATH)/$(PTF)

re: fclean all













