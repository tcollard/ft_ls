# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcollard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/19 13:13:06 by tcollard          #+#    #+#              #
#    Updated: 2018/06/06 13:09:59 by tcollard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, debug, norme

NAME = ft_ls

END = \x1b[0m
GREEN = \x1b[32m

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -L ./libft
LDLIBS = -lft

INCLUDE = ./includes/
PATH_LIB = ./libft/
PATH_SRC = ./srcs/
PATH_OBJ = ./obj/

NAME_SRC =	ft_ls.c \
			dispatch.c \
			error.c \
			display.c \
			info_file.c \
			add_mode.c \
			sort_time.c \
			sort_size.c \
			list.c \
			padding.c \
			option.c \
			sort.c


NAME_OBJ = $(NAME_SRC:.c=.o)

SRC = $(addprefix $(PATH_SRC),$(NAME_SRC))
OBJ = $(addprefix $(PATH_OBJ),$(NAME_OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PATH_LIB)
	@gcc $(CFLAGS) -o $@  $(OBJ) ./libft/libft.a
	@echo "$(NAME):\t\t$(GREEN)[READY]$(END)"

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@gcc $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@make clean -C $(PATH_LIB)
	@rmdir $(PATH_OBJ) 2> /dev/null || true

fclean: clean
	@make fclean -C $(PATH_LIB)
	@rm -f $(NAME)
	@echo "$(NAME):\t\t$(GREEN)[CLEAN]$(END)"

re: fclean all

norme:
	norminette $(SRC)
	norminette ./includes/*.h

debug: $(OBJ)
	make -C ./libft
	gcc $(CFLAGS) $(LDFLAGS) $(LDLIBS) -fsanitize=address -g3 $^ -o $@
