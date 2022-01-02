# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 19:31:14 by ltouret           #+#    #+#              #
#    Updated: 2022/01/02 18:59:40 by ltouret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c utils.c init.c thread_phi.c

OBJS = ${SRCS:.c=.o}

CC		= clang
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -pthread

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		$(CC) ${CFLAGS} $(OBJS) -o $(NAME)

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

test:	all
		./$(NAME) 2 300 100 100 5

.PHONY: all clean fclean re test
