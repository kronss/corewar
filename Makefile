#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abykov <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/05 19:07:36 by abykov            #+#    #+#              #
#    Updated: 2017/06/30 19:42:48 by abykov           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = -Wall -Wextra -Werror


ASM_DIR = asmm
COR_DIR = vm

################################################################################
#	RULES
################################################################################

.PHONY: all clean fclean re

all: 
	@make -C $(COR_DIR)
	@cp vm/corewar .
	@make -C $(ASM_DIR)
	@cp asmm/asm .

clean:
	@make clean -C $(ASM_DIR)
	@make clean -C $(COR_DIR)

fclean: clean
	@make fclean -C $(ASM_DIR)
	@rm -f asm
	@make fclean -C $(COR_DIR)
	@rm -f corewar

re: fclean all
