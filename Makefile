# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marykman <marykman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 18:34:03 by marykman          #+#    #+#              #
#    Updated: 2023/10/28 19:02:11 by marykman         ###   ########.fr        #
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

FT_FOLDER			:=	libft

FT					:=	${FT_FOLDER}/libft.a

MAKE_FT				:=	@make -s -C ${FT_FOLDER}

INCLUDES			:=	-I ${FT_FOLDER}/includes \
						-I ./includes
LIBRARIES			:=	-L./${FT_FOLDER} -lft \

# --------------------------------Source files---------------------------------

NAME				:=	minishell
FILES				:=	main.c
OBJS				:=	$(addprefix objs/, ${FILES:.c=.o})
SRCS				:=	$(addprefix srcs/, ${FILES})
FILES				:=	minishell.h
HEADERS				:=	$(addprefix includes/, ${FILES});

# -----------------------------------Rules-------------------------------------

objs/%.o:	srcs/%.c
	${CC} ${CFLAGS} -c ${INCLUDES} $< -o $@
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