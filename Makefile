# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elchrist <elchrist@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/26 19:56:05 by elchrist          #+#    #+#              #
#    Updated: 2019/09/26 19:57:52 by elchrist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

_SRC =	ant.c \
		ants_contribution.c \
		bfs.c \
		get_pathes.c \
		link.c \
		main.c \
		node.c \
		path.c \
		print.c \
		read_rooms.c \
		read.c \
		sort.c

SRC = $(addprefix src/,$(_SRC))

OBJS = $(patsubst src/%.c,obj/%.o,$(SRC))

FLAGS = -Wall -Wextra -Werror

INC = ./includes

LIBAFIRST = make -C $(LIBRARY)

LIBRARY = libft

$(NAME): $(OBJS)
	@$(LIBAFIRST)
	gcc -o $(NAME) $(OBJS) -I $(INC) -L ./$(LIBRARY) -lft -lftprintf

liba:
	make -C $(LIBRARY)

obj/%.o: src/%.c
	@mkdir -p obj
	gcc -c $(FLAGS) $< -o $@ -I $(INC)

debug:
	gcc -g3 -o $(NAME) $(src) -I $(INC) -L ./$(LIBRARY) -lft -lftprintf

clean:
	rm -f $(OBJS)
	make -C $(LIBRARY) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBRARY) fclean

re: fclean libare $(OBJS)
	gcc -o $(NAME) $(FLAGS) $(OBJS) -I $(INC) -L ./$(LIBRARY) -lft -lftprintf

libare:
	make -C $(LIBRARY) re
