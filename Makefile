# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 18:59:48 by jeberle           #+#    #+#              #
#    Updated: 2024/05/03 17:21:21 by jeberle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=pipex

LIBFT_DIR=libft
LIBFT=libft.a
LIBFT_LIB=$(LIBFT_DIR)/$(LIBFT)

CC=cc
CFLAGS=-Wall -Wextra -Werror
#CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g
LFLAGS=-L$(LIBFT_DIR) -lft

SRCS= \
./pipex.c

OBJ_DIR=obj/
OBJECTS=$(SRCS:%.c=$(OBJ_DIR)%.o)

.PHONY: all clean fclean re libft

all: $(LIBFT_LIB) $(NAME)

-include $(OBJECTS:.o=.d)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

$(LIBFT_LIB):
	@git submodule update --init --recursive --remote > /dev/null 2>&1
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	@$(CC) $(LFLAGS) -o $@ $^
	@echo "\033[32mSUCCESS: pipex\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[31mobjects deleted\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[31mpipex deleted\033[0m"

re: fclean all
