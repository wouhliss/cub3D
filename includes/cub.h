/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:46:02 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/02 18:04:15 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx_int.h>
# include <pthread.h>
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
# define WIDTH 1920
# define HALF_WIDTH 960
# define Q_WIDTH 480
# define H_WIDTH 240
# define HEIGHT 1080
# define HALF_HEIGHT 540
# define Q_HEIGHT 270
# define H_HEIGHT 135
# define MINIMAP_WIDTH 400
# define MINIMAP_HEIGHT 300
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

# define COMPUTING 0
# define RENDERING 1
# define DRAWING 2
# define DRAWN 3
# define ENDED 4

# define CLOSED 0
# define OPEN 1
# define OPENING 2
# define CLOSING 3

# define GROUND 0
# define JUMPING 1
# define FALLING 2

/*GNL*/
# define BUFFER_SIZE 1024
# define EMPTY_BUFFER -42

typedef struct s_buffer
{
	char					buff[BUFFER_SIZE];
	char					*line;
	int						size;
	int						read;
	int						pos;
	int						resume;
}							t_buffer;

typedef struct s_vec
{
	double					x;
	double					y;
}							t_vec;

typedef struct s_intvec
{
	int						x;
	int						y;
}							t_intvec;

typedef struct s_door		t_door;

typedef struct s_door
{
	t_intvec				pos;
	int						state;
	double					frame;
	t_door					*next;
}							t_door;

typedef struct s_render
{
	t_vec					ray_dir;
	t_vec					side_dist;
	t_vec					pside_dist;
	t_vec					tside_dist;
	t_vec					dside_dist;
	t_vec					delta_dist;
	t_vec					transform;
	t_vec					sprite;
	t_vec					pos;
	t_intvec				draw_x;
	t_intvec				draw_y;
	t_intvec				map;
	t_vec					dmap;
	t_intvec				step;
	t_vec					dstep;
	t_intvec				draw;
	t_intvec				pdraw;
	t_intvec				tdraw;
	t_intvec				ddraw;
	t_intvec				tex;
	t_intvec				dtex;
	t_intvec				pixel;
	double					camera_x;
	double					perp_dist;
	double					pperp_dist;
	double					tperp_dist;
	double					dperp_dist;
	double					texpos;
	double					dtexpos;
	double					mystep;
	double					dmystep;
	double					invdet;
	t_door					*door;
	int						spritewidth;
	int						sph;
	int						spsx;
	bool					hit;
	int						phit;
	bool					thit;
	bool					dhit;
	int						side;
	int						pside;
	int						tside;
	int						dside;
	int						line_height;
	int						pline_height;
	int						tline_height;
	int						dline_height;
	int						id;
	int						did;
	int						twidth;
	int						dtwidth;
	int						s;
	int						ds;
	int						portal;
	int						vpos;
}							t_render;

typedef struct s_player
{
	t_vec					pos;
	t_vec					dir;
	t_vec					p;
	t_vec					speed;
	t_vec					delta_dist;
	t_vec					side_dist;
	t_intvec				look_pos;
	t_intvec				step;
	t_intvec				map;
	double					perp_dist;
	bool					looking;
	double					jump;
	int						jumping;
	int						y;
}							t_player;

typedef struct s_map
{
	t_vec					s_pos;
	char					**map;
	char					s_dir;
	int						c_color;
	int						f_color;
}							t_map;

typedef struct s_screen
{
	void					*img;
	char					*addr;
	int						bpp;
	int						ll;
	int						endian;
}							t_screen;
typedef struct s_texture
{
	void					*img;
	char					*addr;
	int						bpp;
	int						ll;
	int						endian;
	int						height;
	int						width;
	int						frames;
	int						f;
	int						s;
}							t_texture;

typedef struct s_mlx
{
	void					*mlx;
	void					*win;
	int						width;
	int						height;
}							t_mlx;

typedef struct s_sprite		t_sprite;

typedef struct s_sprite
{
	t_vec					pos;
	t_vec					dir;
	t_vec					plane;
	t_texture				*t;
	int						type;
	int						vr;
	int						hr;
	int						vpos;
	double					vdiff;
	int						hide;
	int						delete;
	t_sprite				*next;
}							t_sprite;

typedef struct s_projectile	t_projectile;

typedef struct s_projectile
{
	t_sprite				*sprite;
	int						type;
	int						delete;
	t_vec					delta_dist;
	t_vec					side_dist;
	t_intvec				map;
	t_intvec				step;
	double					perp_dist;
	int						side;
	t_projectile			*next;
}							t_projectile;

typedef struct s_portal
{
	t_intvec				pos;
	t_vec					dir;
	t_vec					plane;
	int						side;
}							t_portal;

typedef struct s_game
{
	double					zbuffer[WIDTH][HEIGHT];
	t_map					map;
	t_player				p;
	t_mlx					mlx;
	t_texture				textures[9];
	t_screen				screen;
	t_render				r;
	char					*files[4];
	int						colors_c[4];
	int						colors_f[4];
	t_sprite				*sprites;
	t_sprite				*psprite;
	t_projectile			*projectiles;
	t_door					*doors;
	pthread_mutex_t			state_m;
	pthread_mutex_t			rendered_m[4];
	int						rendered[4];
	t_portal				portal_l;
	t_portal				portal_r;
	double					speed;
	double					sens;
	time_t					now;
	time_t					last;
	time_t					a;
	time_t					f;
	time_t					delta;
	time_t					sync;
	int						texturec;
	int						state;
	int						id;
	int						frames;
	int						fd;
	int						length;
	int						width;
	bool					front;
	bool					back;
	bool					up;
	bool					down;
	bool					left;
	bool					right;
	bool					turn_l;
	bool					turn_r;
	bool					shift;
	bool					minus;
	bool					plus;
	bool					hsprite;
	bool					noclip;
	bool					space;
}							t_game;

typedef struct s_thread
{
	t_game					*game;
	int						id;
	pthread_t				tid;
}							t_thread;

typedef struct s_garbage
{
	void					*content;
	struct s_garbage		*next;
}							t_garbage;

/*events*/

int							on_key_press(int key_code, void *param);
int							on_key_release(int k, void *param);
int							on_destroy_event(void *param);
int							on_mouse(int x, int y, void *param);
// int						logic_loop(void *param);

/*Engine*/

void						ft_drawmap(t_game *game);
void						ft_drawsprites(t_game *game, const int x,
								const int dx);
void						ft_wall(const t_game *game, t_render *r);
void						ft_dwall(const t_game *game, t_render *r);
void						ft_drawpixel(const t_game *game, const int x,
								const int y, t_render *r);
void						ft_ddrawpixel(t_game *game, const int x,
								const int y, t_render *r);
void						*ft_thread(void *arg);
int							ft_loadsprites(t_game *game);
t_projectile				*ft_addprojectile(t_game *game, t_vec pos,
								t_vec dir, int type);
t_door						*ft_adddoor(t_game *game, t_intvec pos);
void						ft_doorsclear(t_game *game);
void						ft_delete_projectile(t_game *game);
void						ft_deletesprite(t_game *game);
void						ft_projectilesclear(t_game *game);
void						ft_pdraw(t_game *game, int x, int w, int y, int h,
								t_portal *p);
void						ft_move(t_game *game);
void						ft_aim(t_game *game);
void						ft_handle_projectiles(t_game *game);
t_door						*ft_getdoor(const t_game *game, const int x,
								const int y);
void						ft_floorceil(t_game *game, const int w,
								const int xx);
/*Parsing*/

void						init_map(char *path, t_game *game);
void						get_info_map(t_game *game);
int							set_colors(char *line, t_game *game);
void						pre_format_map(t_game *game);
void						format_map(t_game *game);
int							check_map(t_game *game);
int							set_texture(char *line, t_game *game);
t_sprite					*ft_addsprite(t_game *game, t_sprite *sprite);
void						ft_spritesclear(t_game *game);
/*Utils*/

char						*get_next_line(int fd);
int							ft_strnchr(t_buffer *buffer);
char						*ft_strchr(char *s, int c);
char						*ft_strrchr(char *s, int c);
int							ft_dprintf(int fd, const char *str, ...);
int							ft_strcmp(const char *s1, const char *s2);
char						*ft_strdup(const char *s);
char						**join_tab(char **map, char *str);
int							ft_strlen(const char *str);
char						**ft_copy(char **map);
int							plen(char **map);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
void						*ft_calloc(size_t nmemb, size_t size);
void						skip_spaces(char *line, int *i);
int							plen(char **map);
int							ft_atoc(const char *str);
int							max(int a, int b);
char						**ft_split(char const *s, char c);
int							create_trgb(int t, int r, int g, int b);
void						put_colors(t_game *game);
void						my_mlx_pixel_put(const t_screen *data, const int x,
								const int y, const int color);
void						my_mlx_pixel_tput(t_screen *data, int x, int y,
								int color);
void						my_mlx_pixel_hput(t_screen *data, int x, int y,
								int color);
void						ft_swapi(int *a, int *b);
void						ft_swapd(double *a, double *b);
int							ft_outside(const t_game *game, const int x,
								const int y);
// int						first_last_line(t_game *game);
// void					display_tab(char **tab);
// int						check_line(t_game *game);
// int						first_last_inline(char *line);
// int						valid_char(char *line, int *player_count);
// int						no_dups(t_game *game);

/*Garbage collector*/

void						*gc(void *ptr, int i);

/*Free and exit*/

void						panic(const char *message);
void						free_tab(char **tab);

#endif
