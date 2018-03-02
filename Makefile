#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/02 13:04:02 by dlytvyn           #+#    #+#              #
#    Updated: 2018/03/02 13:04:03 by dlytvyn          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = dlytvyn.filler
LIBFT = ./libft/libft.a
FT_PRINTF = ./ft_printf/libftprintf.a
GNL = ./GNL/get_next_line.c
COLORS = ./src/colors.c
CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iincludes

FILLER =	./src/main.c\
			./src/ft_free.c\
			./src/get_data.c\
			./src/logic.c\
			./src/logic_2.c\
			./src/logic_3.c\

FILLER_OBJ = $(FILLER:.c=.o)

all: $(NAME)

$(NAME):
	cd libft && make && cp libft.a ../
	cd ft_printf && make && cp libftprintf.a ../
	$(CC) $(CFLAGS) $(FILLER) $(LIBFT) $(FT_PRINTF) $(GNL) -o $(NAME)
	$(CC) $(CFLAGS) $(COLORS) $(LIBFT) $(FT_PRINTF) $(GNL) -o colors
clean:
	cd src && rm -f $(FILLER_OBJ)
	cd libft && make clean
	cd ft_printf && make clean

fclean: clean
	cd ft_printf && make fclean
	cd libft && make fclean
	/bin/rm -f $(NAME)
	/bin/rm -f libftprintf.a
	/bin/rm -f libft.a

re: fclean all