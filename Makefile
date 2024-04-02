CC = gcc	
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3
MLXFLAGS = -L ./minilibx-linux -lmlx -Ilmlx -lXext -lX11 -lm
INCLUDE = -I./includes -Iminilibx-linux
VPATH = srcs/parsing srcs/utils srcs/error srcs/ft_dprintf srcs/gnl srcs/hooks srcs/engine srcs
RM = rm -rvf
NAME = cub3D
NAME_BONUS = cub3D_bonus

UTILS = utils1 utils2 utils3 utils4 utils5 ft_split
PARSING = checkings colors init map format settings textures sprite_parse
ERROR = panic garbage
DPRINTF = ft_dprintf dprintf_utils dprintf_utils2
GNL = gnl
HOOKS = key window
HOOKSB = key_bonus window mouse
ENGINE = render walls minimap sprites projectile projectile_utils movement aim door door_utils floor_ceil

SRCS = $(addsuffix .c, $(UTILS))\
	   $(addsuffix .c, $(PARSING))\
	   $(addsuffix .c, $(ERROR))\
	   $(addsuffix .c, $(DPRINTF))\
	   $(addsuffix .c, $(GNL))\
	   $(addsuffix .c, $(HOOKS))\
	   $(addsuffix .c, $(ENGINE))\
	   main.c
	
SRCSB = $(addsuffix .c, $(UTILS))\
	   	$(addsuffix .c, $(PARSING))\
	   	$(addsuffix .c, $(ERROR))\
	   	$(addsuffix .c, $(DPRINTF))\
	   	$(addsuffix .c, $(GNL))\
	   	$(addsuffix .c, $(HOOKSB))\
	   	$(addsuffix .c, $(ENGINE))\
	   	main_bonus.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

DEPS = $(SRCS:%.c=$(OBJ_DIR)/%.d)

OBJSB = $(SRCSB:%.c=$(OBJ_DIR)/%.o)

DEPSB = $(SRCSB:%.c=$(OBJ_DIR)/%.d)

all: $(NAME) $(NAME_BONUS)

$(NAME): $(OBJ_DIR)  $(OBJS)
	$(MAKE) -C ./minilibx-linux
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(NAME_BONUS): $(OBJ_DIR)  $(OBJSB)
	$(MAKE) -C ./minilibx-linux
	$(CC) $(CFLAGS) $(OBJSB) $(LIBFT) $(MLXFLAGS) -o $(NAME_BONUS)


bonus: 	$(NAME_BONUS)

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c includes/cub.h includes/ft_dprintf.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

-include $(DEPS) $(DEPSB)

.PHONY: all clean fclean re bonus
