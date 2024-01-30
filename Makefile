# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 15:43:35 by ael-mank          #+#    #+#              #
#    Updated: 2024/01/30 15:43:36 by ael-mank         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME_CLIENT = client
NAME_SERVER = server

SRCS_CLIENT = src/client.c
SRCS_SERVER = src/server.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

INCLUDE = include

LIB = $(addprefix $(LIB_PATH), libft.a)

LIB_PATH = libft/

LIB_INCLUDE = libft/include

CC = cc

CFLAGS = -Wall -Wextra -Werror

src/%.o: src/%.c $(INCLUDE)
	$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) -c $< -o $(<:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT) : $(OBJS_CLIENT) $(LIB)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -L $(LIB_PATH) -l ft -o $(NAME_CLIENT)

$(NAME_SERVER) : $(OBJS_SERVER) $(LIB)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -L $(LIB_PATH) -l ft -o $(NAME_SERVER)

$(LIB):
	@cd ./libft && make > /dev/null && make bonus > /dev/null && make printf > /dev/null


clean :
	make clean -C libft
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean : clean
	make fclean -C libft
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re : fclean all

.PHONY : libft all clean fclean re
