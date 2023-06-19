# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juzheng <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 09:44:41 by juzheng           #+#    #+#              #
#    Updated: 2023/06/12 09:44:41 by juzheng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS		=	main.c utils.c ft_init.c threads.c \
					finished_died.c actions.c

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME) $(all)

re:
			fclean $(NAME)

.PHONY:		all clean fclean re