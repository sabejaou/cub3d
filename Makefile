# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 20:10:07 by sbejaoui          #+#    #+#              #
#    Updated: 2024/09/18 17:52:15 by sabejaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBS = libft.a

# *********************************VARIABLES**************************************** #

SRCS_DIR = ./srcs/

SRCS =\
		main.c \

#------PARSING------#
SRCS += $(addprefix parsing/, $(SRCS_PARSING))
SRCS_PARSING=\
		parsing.c \
		mapscan.c \

SRCS := $(SRCS:%=$(SRCS_DIR)%)

OBJS_DIR = ./objs/

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

INCS = ./incl

INCS_LIBS = ./libft/incs

DEPS = $(OBJS:.o=.d)

DEPS_BONUS = $(OBJS_BONUS:.o=.d)

LIBS_TARGET = ./libft/libft.a

MLX_LIB			=	-L./libmlx -lmlx -lXext -lX11

# **********************************COMMANDS**************************************** #

CC = cc

CFLAGS = -Werror -Wextra -Wall -g3 -MMD -MP

CPPFLAGS = -I$(INCS) -I$(INCS_LIBS)

CFSIGSEV = -fsanitize=address

VALGRIND = valgrind -q --leak-check=full --show-reachable=yes

RM = rm -rf

DIR_DUP = mkdir -p $(@D)

AR = ar rcs

MAKEFLAGS += --no-print-directory

# **********************************RULES**************************************** #

all:	$(NAME)

-include $(DEPS)

$(NAME): $(LIBS_TARGET) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -L$(dir $(LIBS_TARGET)) $(MLX_LIB) -lft -lreadline -o $(NAME)

$(LIBS_TARGET): FORCE
	@echo " "
	@echo "\033[1m\033[32m#-------------------------[COMPILATION LIBFT]-------------------------#\033[0m"
	$(MAKE) -C $(@D)
	@echo "\033[1m\033[32m#---------------------------[LIBFT COMPILED]--------------------------#\033[0m"
	@echo "\033[1m\033[32m#-------------------------[COMPILATION LIBMLX]-------------------------#\033[0m"
	$(MAKE) -C ./libmlx
	@echo "\033[1m\033[32m#---------------------------[LIBMLX COMPILED]--------------------------#\033[0m"
	@echo " "

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

fsanitize : fclean $(LIBS_TARGET) $(OBJS) $(INCS)
	$(CC) $(CFLAGS) $(CFSIGSEV) $(CPPFLAGS) $(OBJS) -L$(dir $(LIBS_TARGET)) -lft -lreadline -o $(NAME)

clean :
	$(RM) $(OBJS_DIR)
	$(MAKE) $@ -C ./libft

fclean : clean
	$(RM) $(NAME)
	$(MAKE) $@ -C ./libft
	$(MAKE) clean -C ./libmlx

re : fclean all

print% :
	@echo $(patsubst print%,%,$@)=
	@echo $($(patsubst print%,%,$@)) | tr " " "\n"

.PHONY: all clean fclean re FORCE bonus fsanitize print%
FORCE:

# Colors
BLACK=\033[30m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
PURPLE=\033[35m
CYAN=\033[36m
WHITE=\033[37m

# Text
ERASE=\033[2K\r
RESET=\033[0m
BOLD=\033[1m
FAINT=\033[2m
ITALIC=\033[3m
UNDERLINE=\033[4m




# OBJ_DIR			=	.objs

# MANDATORY_DIR	=	srcs

# SRCS 			=  $(MANDATORY_DIR)/main.c				\

# PARSING_DIR		=	$(MANDATORY_DIR)/parsing
# SRCS += $(addprefix parsing/, $(SRCS_PARSING))
# SRCS_PARSING= $(PARSING_DIR)/parsing.c

# OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# HEADER_SRCS		=	cub3d.h
# HEADERS_DIR		=	incl/
# HEADERS			=	$(addprefix $(HEADERS_DIR), $(HEADER_SRCS))
# CC				=	cc
# RM				=	rm -f
# CFLAGS			=	-O3 -I incl -g3 -Wall -Wextra -Werror
# MLX_LIB			=	-L./libmlx -lmlx -lXext -lX11 -L./libft -lft

# GREEN			=	\033[1;32m
# BLUE			=	\033[1;34m
# RED				=	\033[1;31m
# YELLOW      	=	\033[1;33m
# DEFAULT			=	\033[0m
# UP				=	"\033[A"
# CUT				=	"\033[K"

# $(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c $(HEADERS)
# 	@mkdir -p $(OBJ_DIR)
# 	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
# 	@$(CC) $(CFLAGS) -c $< -o $@
# 	@printf ${UP}${CUT}

# $(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c $(HEADERS)
# 	@mkdir -p $(OBJ_DIR)
# 	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
# 	@$(CC) $(CFLAGS) -c $< -o $@
# 	@printf ${UP}${CUT}

# all: lib $(NAME)

# lib:
# 	@echo "$(YELLOW)Make MLX$(DEFAULT)"
# 	@make -C libmlx
# 	@echo "$(YELLOW)Make libft$(DEFAULT)"
# 	@make -C libft
# 	@echo "$(BLUE)Compiling...$(DEFAULT)"

# $(NAME): $(OBJS)
# 	@$(CC) $(OBJS) $(MLX_LIB) -o $(NAME) -lm
# 	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

# bonus: lib $(OBJS_BONUS)
# 	@$(CC) $(OBJS_BONUS) $(MLX_LIB) -o $(NAME) -lm
# 	@echo "$(GREEN)$(NAME) bonus compiled!$(DEFAULT)"

# clean:
# 	@echo "$(RED)Cleaning build folder$(DEFAULT)"
# 	@$(RM) $(OBJS) $(OBJS_BONUS)

# fclean: clean
# 	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
# 	@$(RM) $(NAME)
# 	@echo "$(RED)Cleaning MLX$(DEFAULT)"
# 	@make -C libmlx clean
# 	@echo "$(RED)Cleaning libft$(DEFAULT)"
# 	@make -C libft fclean
# 	@echo "$(GREEN)ALL CLEAN$(DEFAULT)"

# re:				fclean all

# .PHONY:			all clean fclean re bonus
