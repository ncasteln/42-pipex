# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 15:26:29 by ncasteln          #+#    #+#              #
#    Updated: 2023/08/31 13:09:24 by ncasteln         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *******************************************************************************
#                                                                       VARIABLES
# *******************************************************************************
NAME = pipex
CFLAGS = -g -Wall -Wextra #-Werror

# -------------------------------------------------------------------------- LIB
LIB = $(LIBFT) $(FT_PRINTF) $(GNL)
LIBFT = ./lib/libft/libft.a
FT_PRINTF = ./lib/ft_printf/libftprintf.a
GNL = ./lib/get_next_line/libgnl.a

# ------------------------------------------------------------------------- SRCS
VPATH = ./src/
OBJS_DIR = ./objs/

# ------------------------------------------------------------------------- MAND
SRC = main.c \
	cmd_path.c
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

# ---------------------------------------------------------------------- INCLUDE
INCLUDE = -I ./include/ \
	-I ./lib/libft/include/ \
	-I ./lib/ft_printf/include/ \
	-I ./lib/get_next_line/

# *******************************************************************************
#                                                                           RULES
# *******************************************************************************

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@echo "$(NC)Compiling $@ executable file..."
	@$(CC) \
	$(OBJS) $(LIB) \
	-o $(NAME)
	@echo "$(G)	$@ successfully compiled!";
# add CFLAGS

$(LIB):
	@echo "$(NC)Compiling [libraries]..."
	@$(MAKE) -C ./lib/

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@cc $(CFLAGS) -c $< -o $@ $(INCLUDE)

# ------------------------------------------------------------------- CLEANING
clean:
	@echo "$(NC)Removing [objs]..."
	@rm -rf $(OBJS_DIR)
	@echo "$(NC)Destroying [lib] archives..."
	@$(MAKE) fclean -C ./lib/

fclean: clean
	@echo "$(NC)Removing [$(NAME)]..."
	@rm -f $(NAME)
	@echo "$(G)	[$(NAME)] removed!"




G = \033[0;32m
Y = \033[0;33m
R = \033[0;31m
NC = \033[0m

.PHONY: all clean fclean re bonus
