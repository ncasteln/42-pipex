# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 15:26:29 by ncasteln          #+#    #+#              #
#    Updated: 2023/09/06 14:22:36 by ncasteln         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = -g -Wall -Wextra -Werror

# ------------------------------------------------------------------------- LIB
LIB = $(LIBFT) $(FT_PRINTF) $(GNL)
LIBFT = ./lib/libft/libft.a
INCLUDE_LIBFT = -I./lib/libft/include/
LIBFT_HEADER = libft.h

FT_PRINTF = ./lib/ft_printf/libftprintf.a
INCLUDE_FT_PRINTF = -I./lib/ft_printf/include/
FT_PRINTF_HEADER = libftprintf.h

GNL = ./lib/get_next_line/libgnl.a
INCLUDE_GNL = -I./lib/get_next_line/
GNL_HEADER = ./lib/get_next_line/get_next_line.h

# ------------------------------------------------------------------------ SRCS
VPATH = ./src/:./src_bonus/
OBJS_DIR = ./objs/

# ------------------------------------------------------------------------ MAND
SRC = main.c \
	get_env_var.c \
	parse_cmd.c \
	first_child.c \
	last_child.c \
	error.c \
	parent.c \
	print_utils.c
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))
OBJS_FLAG = $(OBJS_DIR).mand_flag

# ----------------------------------------------------------------------- BONUS
SRC_BONUS = main_bonus.c \
	get_env_var_bonus.c \
	fd_creation_bonus.c \
	here_doc_bonus.c \
	parse_cmd_bonus.c \
	first_child_bonus.c \
	mid_child_bonus.c \
	last_child_bonus.c \
	error_bonus.c \
	parent_bonus.c \
	free_utils_bonus.c \
	print_utils_bonus.c
ifneq ($(filter bonus,$(MAKECMDGOALS)),)
	OBJS = $(addprefix $(OBJS_DIR), $(SRC_BONUS:.c=.o))
	OBJS_FLAG = $(OBJS_DIR).bonus_flag
endif

# --------------------------------------------------------------------- INCLUDE
INCLUDE = -I./include/ $(INCLUDE_LIBFT) $(INCLUDE_FT_PRINTF) $(INCLUDE_GNL)
HEADER = ./include/pipex.h

# ----------------------------------------------------------------------- RULES
all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIB) $(OBJS) $(OBJS_FLAG)
	@echo "$(NC)Compiling $@ executable file..."
	@$(CC) $(CFLAGS) \
	$(OBJS) $(LIB) \
	-o $(NAME)
	@echo "$(G)	$@ successfully compiled!$(NC)";

$(LIB):
	@echo "$(NC)Compiling [libraries]..."
	@$(MAKE) -C ./lib/

$(OBJS_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
	@cc $(CFLAGS) -c $< -o $@ $(INCLUDE)

# [objs_flag] make possible to re-make the exe file alternately between
# 'all' and 'bonus' rule, without clean or fclean them
$(OBJS_FLAG):
	@rm -rf $(OBJS_DIR).mand_flag
	@rm -rf $(OBJS_DIR).bonus_flag
	@mkdir -p $(OBJS_DIR)
	@touch $(OBJS_FLAG)
	@echo "$(Y)	Created [objs_flag]"

# -------------------------------------------------------------------- CLEANING
clean:
	@echo "$(NC)Removing [objs]..."
	@rm -rf $(OBJS_DIR)
	@echo "$(NC)Destroying [lib] archives..."
	@$(MAKE) fclean -C ./lib/

fclean: clean
	@echo "$(NC)Removing [$(NAME)]..."
	@rm -f $(NAME)
	@echo "$(G)	[$(NAME)] removed!$(NC)"

re: clean fclean all

G = \033[0;32m
Y = \033[0;33m
R = \033[0;31m
NC = \033[0m

.PHONY: all clean fclean re bonus
