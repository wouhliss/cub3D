CC = gcc-12 
CFLAGS = -Wall -Wextra -Werror -MMD -MP -march=native -O3 $(EXTRAFLAGS)
MLXPATH = minilibx-linux/
MLXFLAGS = -L $(MLXPATH) -lmlx -Ilmlx -lXext -lX11 -lm
LIBMLX = $(MLXPATH)/libmlx.a
INCLUDE_PATH = ./includes/
INCLUDE = -I$(INCLUDE_PATH) -I./minilibx-linux
VPATH = srcs/parsing srcs/utils srcs/error srcs/ft_dprintf srcs/gnl srcs/hooks srcs/engine srcs
RM = rm -rvf
NAME = cub3D
NAME_BONUS = cub3D_bonus

UTILS = utils1 utils2 utils3 utils4 utils5 utils6 ft_split vector vector_utils
PARSING = checkings colors init map format settings textures
ERROR = panic garbage
DPRINTF = ft_dprintf dprintf_utils dprintf_utils2
GNL = gnl
HOOKS = key_bonus window mouse block_utils sprite_utils
ENGINE = glass_utils import_textures mlx render loop walls movement aim minimap doors hit sprites collisions glass portal portal_utils portal_utils2 projectile projectile_utils projectile_utils2 truc animation
ENGINEB = glass_utils import_textures mlx render loop_bonus walls movement aim minimap doors hit sprites collisions glass portal portal_utils portal_utils2 projectile projectile_utils projectile_utils2 truc animation

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
	   	$(addsuffix .c, $(HOOKS))\
	   	$(addsuffix .c, $(ENGINEB))\
	   	main.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

DEPS = $(SRCS:%.c=$(OBJ_DIR)/%.d)

OBJSB = $(SRCSB:%.c=$(OBJ_DIR)/%.o)

DEPSB = $(SRCSB:%.c=$(OBJ_DIR)/%.d)


all:
	make -j $(NAME)


$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)


$(NAME_BONUS): $(OBJ_DIR) $(OBJSB)
	$(CC) $(CFLAGS) $(OBJSB) $(LIBFT) $(MLXFLAGS) -o $(NAME_BONUS)


$(LIBMLX):
	wget https://cdn.intra.42.fr/document/document/22794/minilibx-linux.tgz
	tar -xf minilibx-linux.tgz
	rm minilibx-linux.tgz
	make -C $(MLXPATH)


$(OBJ_DIR):
	mkdir -p obj


$(OBJ_DIR)/%.o: %.c $(INCLUDE_PATH)cub.h $(INCLUDE_PATH)ft_dprintf.h $(LIBMLX)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)


clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(MLXPATH)


fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)


bonus:
	make -j $(NAME_BONUS)


re: fclean
	make -j $(NAME)


rebonus: fclean
	make -j $(NAME_BONUS)


-include $(DEPS) $(DEPSB)


.PHONY: all clean fclean re bonus rebonus
