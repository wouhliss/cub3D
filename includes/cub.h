/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:46:02 by ybelatar          #+#    #+#             */
/*   Updated: 2024/02/21 16:00:07 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define PI 3.14f

# define ON_KEYPRESS 2
# define ON_KEYRELEASE 3
# define ON_MOUSEPRESS 4
# define ON_DESTROY 17
# define NO_MASK 0L
# define KEYPRESS_MASK 1L
# define KEYRELEASE_MASK 2L
# define BUTTONPRESS_MASK 4L
# define CURSOR_RADIUS 10

# define ERR_FORMAT "%s: %s\n"
# define NAME "cub3D"
# define EXT ".cub"
# define ARGS_ERR "Wrong number of args specified (./game <map.cub>)."
# define EXT_ERR "Wrong file extension specified (./game <map.cub>)."
# define MALLOC_ERR "Could not allocate memory."
# define FILE_ERR "Could not open map file."
# define MAP_ERR "Something went wrong while parsing map file."

# define WIDTH 1280
# define HEIGHT 720
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define MAGENTA_BURST 0xFF00FF
# define LIME_SHOCK 0xCCFF00
# define NEON_ORANGE 0xFF6600
# define PSYCHEDELIC_PURPLE 0x660066
# define AQUA_DREAM 0x33CCCC
# define HOT_PINK 0xFF66B2
# define ELECTRIC_BLUE 0x0066FF
# define LAVA_RED 0xFF3300

typedef struct s_pos
{
	float				x;
	float				y;
}						t_pos;

typedef struct s_player
{
	t_pos				pos;
	float				angle;
}						t_player;

typedef struct s_map
{
	char				**map;
	char				start_direction;
}						t_map;

typedef struct s_texture
{
	void				*img;
	char				*addr;
	int					bpp;
	int					ll;
	int					endian;
}						t_texture;

typedef struct s_game
{
	int					fd;
	int					length;
	int					width;
	int					colors_c[4];
	int					colors_f[4];
	t_map				map;
	t_player			player;
	char				*textures[4];
}						t_game;

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}						t_garbage;

/*Parsing*/

void					init_map(char *path, t_game *game);
void					get_info_map(t_game *game);
int						set_colors(char *line, t_game *game);
int						set_texture(char *line, t_game *game);
void					pre_format_map(t_game *game);
void					format_map(t_game *game);
int						check_map(t_game *game);

/*Utils*/

char					*ft_strchr(char *s, int c);
int						ft_dprintf(int fd, const char *str, ...);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strdup(const char *s);
char					**join_tab(char **map, char *str);
int						ft_strlen(const char *str);
char					**ft_copy(char **map);
int						plen(char **map);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
void					skip_spaces(char *line, int *i);
int						plen(char **map);
int						ft_atoc(const char *str);
int						max(int a, int b);
char					**ft_split(char const *s, char c);

// int						first_last_line(t_game *game);
// void					display_tab(char **tab);
// int						check_line(t_game *game);
// int						first_last_inline(char *line);
// int						valid_char(char *line, int *player_count);
// int						no_dups(t_game *game);

/*Garbage collector*/

void					*gc(void *ptr, int i);

/*Free and exit*/

void					panic(const char *message);
void					free_tab(char **tab);

#endif
