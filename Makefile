# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aloubier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 12:58:01 by aloubier          #+#    #+#              #
#    Updated: 2023/04/28 18:59:48 by aloubier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mlx_lp
SRCDIR = src
INCDIR = includes
OBJ_DIR = build

SRC = $(SRCDIR)/main.c $(SRCDIR)/window.c $(SRCDIR)/draw.c $(SRCDIR)/utils.c $(SRCDIR)/mandelbrot.c $(SRCDIR)/complex.c

OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJ_DIR)/%.o)
LIB = -lft -lmlx -lXext -lX11 -lm
CC = gcc

CFLAGS = -O3 -Wall -Wextra -Werror -I$(INCDIR)

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -L libft -L minilibx $(OBJ) $(LIB) 

$(OBJ_DIR)/%.o:	$(SRCDIR)/%.c
	mkdir -p '$(@D)'
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
