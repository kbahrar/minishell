# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/23 19:48:26 by kbahrar           #+#    #+#              #
#    Updated: 2019/07/23 19:58:42 by kbahrar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = src/main.c src/ft_alias.c src/access_file.c src/do_cd.c src/read_line.c src/ft_vars.c src/sh_split.c src/setenv.c src/unsetenv.c src/free_list.c src/ft_echo.c src/make_env.c src/ft_signal.c src/home_path.c src/var_dol.c
OBJ = $(SRC:.c=.o)
LIBF = libft/libft.a
LIBS = minish.a

all:$(NAME)

$(NAME): $(OBJ)
	make -C libft
	@ar rc $(LIBS) $(OBJ)
	gcc -Wall -Wextra -Werror $(LIBS) $(LIBF) -o $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf $(LIBS)
	make fclean -C libft/

fclean: clean
	rm -rf $(NAME)

re: fclean all
	make re -C libft/

%.o : %.c
	gcc -Wall -Wextra -Werror -c $< -o $@
