# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 20:10:07 by sbejaoui          #+#    #+#              #
#    Updated: 2024/09/17 11:55:15 by sabejaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MANDATORY_DIR	=	srcs
OBJ_DIR			=	.objs

SRCS =  $(MANDATORY_DIR)/main.c				\

OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

HEADER_SRCS		=	cub3d.h
HEADERS_DIR		=	incl/
HEADERS			=	$(addprefix $(HEADERS_DIR), $(HEADER_SRCS))
CC				=	cc
RM				=	rm -f
CFLAGS			=	-O3 -I incl -g3 -Wall -Wextra -Werror
MLX_LIB			=	-L./libmlx -lmlx -lXext -lX11 -L./libft -lft
NAME			=	cub3d

GREEN			=	\033[1;32m
BLUE			=	\033[1;34m
RED				=	\033[1;31m
YELLOW      	=	\033[1;33m
DEFAULT			=	\033[0m
UP				=	"\033[A"
CUT				=	"\033[K"

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf ${UP}${CUT}

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf ${UP}${CUT}

all: lib $(NAME)

lib:
	@echo "$(YELLOW)Make MLX$(DEFAULT)"
	@make -C libmlx
	@echo "$(YELLOW)Make libft$(DEFAULT)"
	@make -C libft
	@echo "$(BLUE)Compiling...$(DEFAULT)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(MLX_LIB) -o $(NAME) -lm
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

bonus: lib $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(MLX_LIB) -o $(NAME) -lm
	@echo "$(GREEN)$(NAME) bonus compiled!$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning build folder$(DEFAULT)"
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@$(RM) $(NAME)
	@echo "$(RED)Cleaning MLX$(DEFAULT)"
	@make -C libmlx clean
	@echo "$(RED)Cleaning libft$(DEFAULT)"
	@make -C libft fclean
	@echo "$(GREEN)ALL CLEAN$(DEFAULT)"

re:				fclean all

.PHONY:			all clean fclean re bonus
