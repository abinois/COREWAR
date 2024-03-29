# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abinois <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 09:33:50 by abinois           #+#    #+#              #
#    Updated: 2019/09/19 19:54:59 by abinois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRCS = $(addprefix $(SRCDIR)/, $(addsuffix .c, \
	   corewar champtools header param label \
	   tools errors param_tools))

OBJ = $(SRCS:.c=.o)
DEP = $(SRCS:.c=.d)

SRCDIR = src
LIBFT = ../libft/libft.a
LIBFTPRINTF = ../libftprintf.a
LIBMLX = ../libmlx.a
INC = -I include -I ../libft

FLAGS = -Wall -Wextra -Werror
CC = gcc $(INC) $(FLAGS)
FRAMEWORKS = -framework OpenGL -framework AppKit

BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
UNDER = \033[4m
BLINK = \033[5m
REVERSE = \033[7m
NOCOLOR = \033[0m

NB_FILE = $(words $(SRCS))
CPT = 1

all : $(NAME)


$(NAME) : $(LIBFT) $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBFTPRINTF)
	@echo "\n$(BLINK)👌  $(NOCOLOR)$(GREEN)ASSEMBLEUR$(NOCOLOR)$(BLINK) 👌 $(NOCOLOR)"

-include $(DEP)

$(SRCDIR)/%.o : $(SRCDIR)/%.c makefile
	@echo "\033[K$(BLUE)Compilation of file$(NOCOLOR) [$(CPT) / $(NB_FILE)] : $(GREEN)$<\033[A$(NOCOLOR)"
	$(eval CPT=$(shell echo $$(($(CPT) + 1))))
	@gcc $(FLAGS) $(INC) -MMD -MP -c $< -o $@ 

$(LIBFT) : force
	@make -C ../libft
force :

clean :
	@make clean -C ../libft
	@rm -f $(OBJ)
	@echo "$(MAGENTA)SUPPR  $(YELLOW)OBJ $(MAGENTA): $(GREEN) OK !$(NOCOLOR)"
	@rm -f $(DEP)
	@echo "$(MAGENTA)SUPPR  $(YELLOW)DEP $(MAGENTA): $(GREEN) OK !$(NOCOLOR)"
	@echo "$(GREEN)ASM CLEAN : 👌 $(NOCOLOR)"

fclean : clean
	@make fclean -C ../libft
	@echo "$(MAGENTA)SUPPR  $(YELLOW)EXE$(MAGENTA): $(RED)$(NAME)$(NOCOLOR)"
	@rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean re all force
