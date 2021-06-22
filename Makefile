# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 10:50:45 by thsembel          #+#    #+#              #
#    Updated: 2021/06/22 18:49:23 by thsembel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC = \033[0m
RED = \033[0;91m
ORANGE = \033[93m
GREEN = \033[0;92m
PURPLE = \033[0;95m
BLUE = \033[0;34m
BOLD = \033[1m

SRCS		=	./srcs/minishell.c\
				./srcs/env_cpy.c\
				./srcs/ft_error.c\
				./srcs/free_functions.c\
				./srcs/fill_cmds.c\
				./srcs/find_exec.c\
				./srcs/cmd_manager.c\
				./srcs/env_manager.c\
				./srcs/builtin/exec_exit.c\
				./srcs/builtin/exec_cd.c\
				./srcs/builtin/exec_pwd.c\
				./srcs/builtin/exec_env.c\
				./srcs/builtin/exec_unset.c\
				./srcs/builtin/exec_echo.c\
				./srcs/builtin/exec_export.c\
				./srcs/parse.c\
				./srcs/redirection.c\
				./srcs/utils.c


INCLUDES	=	./includes/libft.h\
				./includes/ft_printf.h\
				./includes/minishell.h

HEAD		= ./includes/

LIBFT		= ./libft/libft.a

LIB_DIR	= ./libft/

NAME		= minishell

CC			=	clang

CFLAGS		= 	-Wall -Wextra -Werror -c -fsanitize=address

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -g

.c.o:
		@${CC} ${CFLAGS} -I${HEAD} -c $< -o ${<:.c=.o}
		@echo "${GREEN}[ OK ]	${ORANGE}${<:.s=.o}${NC}"

${NAME}:	${OBJS}
			@make -C ${LIB_DIR}
			@make -C ${LIB_DIR} bonus
			@echo "${GREEN}\nlibft.a		has been created"
			@${CC} ${CFLAGS} -I${HEAD} ${LIBFT} -lreadline -lncurses -o ${NAME} $(OBJS)
			@echo "minishell	has been created${NC}"

all:		${NAME}

clean:
			@make -C $(LIB_DIR) clean
			@${RM} ${OBJS}
			@echo "${GREEN}[ OK ]${RED}	*.o files	deleted${NC}"

fclean:		clean
			@make -C $(LIB_DIR) fclean
			@echo "${GREEN}[ OK ]${RED}	libft.a		deleted${NC}"
			@${RM} ${NAME}
			@echo "${GREEN}[ OK ]${RED}	minishell	deleted${NC}"

re :		fclean all

.PHONY:		all	clean	fclean re
