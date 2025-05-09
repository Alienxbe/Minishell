# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marykman <marykman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 22:37:40 by marykman          #+#    #+#              #
#    Updated: 2025/05/09 15:19:05 by marykman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -----------------------------------Colors------------------------------------

RED				:=	\033[38;5;9m
GREEN			:=	\033[38;5;10m
BLUE			:= 	\033[38;5;14m
YELLOW			:=	\033[38;5;226m
LIGHT_BLUE		:=	\033[38;5;14m
RESET			:=	\033[38;5;7m
PREFIX			=	[${LIGHT_BLUE}${NAME}${RESET}]\t

# ---------------------------------Compilation---------------------------------

CC					:=	@gcc
CFLAGS				:=	-Wall -Wextra -Werror
RM					:=	@rm -f

# ---------------------------------Librairies----------------------------------

FT_FOLDER			:=	libs/libft

FT					:=	${FT_FOLDER}/libft.a

MAKE_FT				:=	@make -s -C ${FT_FOLDER}

INCLUDES			:=	-I ${FT_FOLDER}/includes \
						-I ./includes
LIBRARIES			:=	-L./${FT_FOLDER} -lft \
						-lreadline

# --------------------------------Source files---------------------------------

NAME				:=	minishell

FILES				:=	minishell.h
HEADERS				:=	$(addprefix includes/, ${FILES});

FILES				:=	main.c
FILES_EXEC			:=	path.c \
						redirs.c \
						exec.c
FILES_PARSING		:=	parsing.c \
						cmd.c \
						token.c \
						redir.c \
						utils.c
FILES_ENV			:=	add.c \
						cat.c \
						del.c \
						get.c \
						utils.c
FILES_BUILTINS		:=	error.c \
						ft_builtins.c \
						ft_cd.c \
						ft_echo.c \
						ft_env.c \
						ft_exit.c \
						ft_export.c \
						ft_pwd.c \
						ft_unset.c

SRCS				:=	$(addprefix srcs/, ${FILES})
SRCS				+=	$(addprefix srcs/parsing/, ${FILES_PARSING})
SRCS				+=	$(addprefix srcs/exec/, ${FILES_EXEC})
SRCS				+=	$(addprefix srcs/env/, ${FILES_ENV})
SRCS				+=	$(addprefix srcs/builtins/, ${FILES_BUILTINS})
OBJS				:=	$(patsubst srcs%.c, objs%.o, ${SRCS})

# -----------------------------------Rules-------------------------------------

objs/%.o:	srcs/%.c ${HEADERS}
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@
	@echo "${PREFIX}Compilation of $<..."

$(NAME):	${FT} ${OBJS} ${HEADERS}
	${CC} ${CFLAGS} ${OBJS} ${LIBRARIES} -o $@
	@echo "${PREFIX}$@ Compiled !"

$(FT):
	${MAKE_FT}

all:	${NAME}

clean:
	${RM} ${OBJS}
	${MAKE_FT} clean

fclean:
	${RM} ${OBJS} ${NAME}
	${MAKE_FT} fclean

re:		fclean all

# -----------------------------------.PHONY------------------------------------

.PHONY:	all clean fclean re
