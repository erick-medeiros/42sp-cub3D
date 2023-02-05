# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 14:02:31 by frosa-ma          #+#    #+#              #
#    Updated: 2022/08/10 05:35:17 by frosa-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY	= all clean fclean re bonus

NAME	= libftprintf.a

CC		= clang
CFLAGS	= -Wall -Werror -Wextra
INC		= -I. -I..

LIB		= ../libft.a
SRCS	= \
	ft_printf.c \
	ft_printf_utils.c \
	dot_disp.c \
	dot_wr.c \
	dot.c \
	minus_disp.c \
	minus_wr.c \
	minus.c \
	space_disp.c \
	space_wr.c \
	space.c \
	zero_disp.c \
	zero_wr.c \
	zero.c \
	sharp.c \
	plus.c

OBJSDIR	= obj
OBJS	= $(addprefix ${OBJSDIR}/, ${SRCS:%.c=%.o})

all: ${NAME}

${NAME}: | ${LIB} ${OBJSDIR} ${OBJS}
	ar -rcs $@ $^

${LIB}:
	${MAKE} -C libft/

${OBJSDIR}:
	mkdir -p $@

${OBJSDIR}/%.o: %.c
	${CC} ${CFLAGS} ${INC} -c $< -o $@

bonus: all

clean:
	rm -rf ${OBJSDIR}

fclean: clean
	rm -rf ${NAME}

re: fclean all
