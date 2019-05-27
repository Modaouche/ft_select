# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/20 17:03:40 by modaouch          #+#    #+#              #
#    Updated: 2019/02/02 17:28:46 by modaouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

SRC =	srcs/main.c\
		srcs/ft_select.c\
		srcs/ft_set_term.c\
		srcs/ft_signal_handler.c\
		srcs/dlist.c\
		srcs/dlist2.c\
		srcs/tools.c\
		srcs/tools2.c\
		srcs/tools3.c\
		srcs/ft_key.c\
		srcs/ft_key2.c\
		srcs/ft_exit.c

LIB = libft/libft.a\
	  libft/ft_printf/libftprintf.a\

OBJ = $(SRC:.c=.o)
#OBJ = $(patsubst %.c,%.o, $(SRC))

INCLUDES = libft/ft_printf/includes/ft_conv.h\
		   libft/ft_printf/includes/ft_printf.h\
		   libft/libft.h\
		   includes/ft_select.h

LIBFT = libft

LIBFTPRINTF = libft/ft_printf/

DIRPRINTF = libft/ft_printf/src\
		    libft/ft_printf/includes\
		    libft/ft_printf/src/libft

DEPEN = $(INCLUDES) $(SRC) $(OBJ) Makefile libft/Makefile\
		libft/ft_printf/Makefile $(LIBFT) $(LIBFTPRINTF) srcs

CC = gcc

CFLAGS +=  -Wall -Wextra -Werror\
		#  -g -fsanitize=address\
		  -fno-omit-frame-pointer\
		  -fsanitize-address-use-after-scope

all: $(NAME)


$(NAME): $(DEPEN)
	make -C $(LIBFT) all
	make -C $(LIBFTPRINTF) all
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lncurses

clean:
	make clean -C $(LIBFT)
	make clean -C $(LIBFTPRINTF)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIBFT)
	make fclean -C $(LIBFTPRINTF)
	/bin/rm -f $(OBJ)
	/bin/rm -f ./$(NAME)
help:
	@echo Usage: make [rules]
	@echo "            [all] or just make : compile the project and create an executable $(NAME)"
	@echo "            [clean] : remove all object file"
	@echo "            [fclean] : remove all object file and static library"
	@echo "            [re] : remove all object file, static library and compile the project and create an executable $(NAME)"

re: fclean all
