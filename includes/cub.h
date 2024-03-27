/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:46:02 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/27 15:43:54 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx_int.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <unistd.h>

# define PI 3.141592653589793
# define HALF_PI 1.57079632679

# define ON_KEYPRESS 2
# define ON_KEYRELEASE 3
# define ON_MOUSEPRESS 4
# define ON_MOUSEMOVE 6
# define ON_DESTROY 17
# define NO_MASK 0L
# define KEYPRESS_MASK 1L
# define KEYRELEASE_MASK 2L
# define BUTTONPRESS_MASK 4L
# define POINTERMOTION_MASK 1L << 6
# define CURSOR_RADIUS 10

# define TEXTURES 4

# define ERR_FORMAT "%s: %s\n"
# define NAME "cub3D"
# define EXT ".cub"
# define ARGS_ERR "Wrong number of args specified (./game <map.cub>)."
# define EXT_ERR "Wrong file extension specified (./game <map.cub>)."
# define MALLOC_ERR "Could not allocate memory."
# define FILE_ERR "Could not open map file."
# define MAP_ERR "Something went wrong while parsing map file."
# define CHAR_ERR "Invalid char found in map file."
# define EMPTYL_ERR "Empty line found in map file."
# define EMPTY_ERR "Map file is empty."
# define TEXTURE_ERR "Could not parse textures."
# define TEXTURE_SIZE "Invalid texture size."
# define MLX_ERR "Could not load the mlx."
# define WIN_ERR "Could not create the window."
# define SCREEN_ERR "Could not create the screen image."
# define IMPORT_ERR "Could not import a texture file."
# define SETTINGS_ERR "Some information are missing from the map file."
# define MISSING_ERR "Invalid or no map was found in file."
# define INVALID_ERR "Invalid/duplicate texture or color found in file"

# define FOV
# define WIDTH 1280
# define HALF_WIDTH 640
# define HEIGHT 720
# define HALF_HEIGHT 360
# define MINIMAP_WIDTH 240
# define MINIMAP_HEIGHT 120
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

/*GNL*/
# define BUFFER_SIZE 1024
# define EMPTY_BUFFER -42

typedef struct s_buffer
{
	char				buff[BUFFER_SIZE];
	char				*line;
	int					size;
	int					read;
	int					pos;
	int					resume;
}						t_buffer;

typedef struct s_vec
{
	double				x;
	double				y;
}						t_vec;

typedef struct s_intvec
{
	int					x;
	int					y;
}						t_intvec;

typedef struct s_render
{
	double				zbuffer[WIDTH];
	t_vec				ray_dir;
	t_vec				side_dist;
	t_vec				delta_dist;
	t_vec				transform;
	t_vec				sprite;
	t_intvec			draw_x;
	t_intvec			draw_y;
	t_intvec			map;
	t_intvec			step;
	t_intvec			draw;
	t_intvec			tex;
	double				camera_x;
	double				perp_dist;
	double				texpos;
	double				mystep;
	double				invdet;
	int					spritewidth;
	int					sph;
	int					spsx;
	int					hit;
	int					side;
	int					line_height;
	int					id;
	int					twidth;
}						t_render;

typedef struct s_player
{
	t_vec				pos;
	t_vec				dir;
	t_vec				plane;
	t_vec				speed;
	int					y;
}						t_player;

typedef struct s_map
{
	t_vec				s_pos;
	char				**map;
	char				s_dir;
	int					c_color;
	int					f_color;
}						t_map;

typedef struct s_screen
{
	void				*img;
	char				*addr;
	int					bpp;
	int					ll;
	int					endian;
}						t_screen;
typedef struct s_texture
{
	void				*img;
	char				*addr;
	int					bpp;
	int					ll;
	int					endian;
	int					height;
	int					width;
}						t_texture;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	int					width;
	int					height;
}						t_mlx;

typedef struct s_sprite
{
	t_vec				pos;
	t_texture			*t;
	int					type;
	int					vr;
	int					hr;
	int					vpos;
	double				vdiff;
}						t_sprite;

typedef struct s_game
{
	t_map				map;
	t_player			p;
	t_mlx				mlx;
	t_texture			textures[5];
	t_screen			screen;
	t_render			r;
	char				*files[4];
	int					colors_c[4];
	int					colors_f[4];
	t_sprite			*sprites;
	int					*sprite_order;
	double				*sprite_dist;
	clock_t				last;
	clock_t				now;
	int					numsprites;
	int					fd;
	int					length;
	int					width;
	int					front;
	int					back;
	int					up;
	int					down;
	int					left;
	int					right;
	int					turn_l;
	int					turn_r;
	int					minus;
	int					plus;
}						t_game;

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}						t_garbage;

/*events*/

int						on_key_press(int key_code, void *param);
int						on_key_release(int k, void *param);
int						on_destroy_event(void *param);
int						on_mouse(int x, int y, void *param);
// int						logic_loop(void *param);

/*Engine*/

void					ft_draw(t_game *game);
void					ft_drawmap(t_game *game, int x, int y);
void					ft_drawsprites(t_game *game);
void					ft_wall(t_game *game);
void					ft_drawpixel(t_game *game, int x, int y);
/*Parsing*/

void					init_map(char *path, t_game *game);
void					get_info_map(t_game *game);
int						set_colors(char *line, t_game *game);
void					pre_format_map(t_game *game);
void					format_map(t_game *game);
int						check_map(t_game *game);
int						set_texture(char *line, t_game *game);
/*Utils*/

char					*get_next_line(int fd);
int						ft_strnchr(t_buffer *buffer);
char					*ft_strchr(char *s, int c);
char					*ft_strrchr(char *s, int c);
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
int						create_trgb(int t, int r, int g, int b);
void					put_colors(t_game *game);
void					my_mlx_pixel_put(t_screen *data, int x, int y,
							int color);
void					ft_swapi(int *a, int *b);
void					ft_swapd(double *a, double *b);
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
