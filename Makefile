# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marykman <marykman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 22:37:40 by marykman          #+#    #+#              #
#    Updated: 2025/02/13 12:33:32 by marykman         ###   ########.fr        #
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
FILES_EXEC			:=	exec.c
FILES_PARSING		:=	parsing.c \
						cmd.c \
						token.c \
						redir.c \
						utils.c
FILES_ENV			:=	env.c \
						utils.c

SRCS				:=	$(addprefix srcs/, ${FILES})
SRCS				+=	$(addprefix srcs/parsing/, ${FILES_PARSING})
SRCS				+=	$(addprefix srcs/exec/, ${FILES_EXEC})
SRCS				+=	$(addprefix srcs/env/, ${FILES_ENV})
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
