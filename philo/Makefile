# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 18:46:22 by bolcay            #+#    #+#              #
#    Updated: 2025/06/06 15:08:48 by bolcay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = init.c philosophers.c philo_utils.c philo_utils1.c clean_up.c philo_actions.c

OBJS = $(SRCS:.c=.o)
NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
