# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 18:59:48 by jeberle           #+#    #+#              #
#    Updated: 2024/05/24 16:35:00 by jonathanebe      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#--------------                       PRINT                       -------------#
#------------------------------------------------------------------------------#

RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
MAGENTA := \033[35m
CYAN := \033[36m
X := \033[0m

SUCCESS := \n$(YELLOW)\
█████████████████████████████████████$(X)\n\
$(X)\n\
███████  █  ███████  ███████  ██   ██$(X)\n\
█     █  █  █     █  █          █ █  $(X)\n\
███████  █  ███████  ███████     █   $(X)\n\
█        █  █        █          █ █  $(X)\n\
█        █  █        ███████  ██   ██$(X)\n\
$(X)\n\
$(YELLOW)█████████████████████████████████████$(X)\n\


#------------------------------------------------------------------------------#
#--------------                      GENERAL                      -------------#
#------------------------------------------------------------------------------#

NAME=pipex

#------------------------------------------------------------------------------#
#--------------                       FLAGS                       -------------#
#------------------------------------------------------------------------------#

CC=cc
CFLAGS=-Wall -Wextra -Werror
ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address -g
endif
DEPFLAGS=-MMD -MP

#------------------------------------------------------------------------------#
#--------------                        DIR                        -------------#
#------------------------------------------------------------------------------#

OBJ_DIR := ./obj
DEP_DIR := $(OBJ_DIR)/.deps
INC_DIRS := .
SRC_DIRS := .

vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIRS)
vpath %.d $(DEP_DIR)

#------------------------------------------------------------------------------#
#--------------                        LIBS                       -------------#
#------------------------------------------------------------------------------#

LIBFT_DIR=libft
LIBFT=libft.a
LIBFT_LIB=$(LIBFT_DIR)/$(LIBFT)
LIBFTFLAGS=-L$(LIBFT_DIR) -lft

#------------------------------------------------------------------------------#
#--------------                        SRC                        -------------#
#------------------------------------------------------------------------------#

SRCS= \
pipex.c \
env.c \
helper.c \
helper2.c \
wait.c \
open.c \
exec.c

#------------------------------------------------------------------------------#
#--------------                      OBJECTS                      -------------#
#------------------------------------------------------------------------------#

OBJECTS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

#------------------------------------------------------------------------------#
#--------------                      COMPILE                      -------------#
#------------------------------------------------------------------------------#

.PHONY: all clean fclean re libft

all: $(LIBFT_LIB) $(NAME)

bonus: all

-include $(OBJECTS:.o=.d)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(LIBFT_LIB):
	@git submodule update --init --recursive --remote > /dev/null 2>&1
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	@$(CC) -o $@ $^ $(LIBFTFLAGS)
	@echo "$(GREEN)SUCCESS:$(X)\n$(SUCCESS)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[31mobjects deleted\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[31mpipex deleted\033[0m"

re: fclean all
