/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:46:02 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/05 14:58:49 by wouhliss         ###   ########.fr       */
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

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEMOVE 6
# define ON_DESTROY 17
# define NO_MASK 0L
# define KEYPRESS_MASK 1L
# define KEYRELEASE_MASK 2L
# define BUTTONPRESS_MASK 4L
# define POINTERMOTION_MASK 64L
# define CURSOR_RADIUS 10

# define WTEXTURES 6
# define STEXTURES 7
# define PTEXTURES 4

# define TNO 0
# define TSO 1
# define TWE 2
# define TEA 3
# define TD 4
# define TB 5

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

# ifndef THREADS
#  define THREADS 2
# endif
# define WIDTH 1280
# define HW WIDTH / 2
# define T_WIDTH WIDTH / THREADS
# define HEIGHT 720
# define HALF_HEIGHT HEIGHT / 2
# define MW 300
# define MH 200
# define MX 60
# define MY 30
# define MS 3
# define MPR 10
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

# define TDRAWING 0
# define COMPLETED 1

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

# define EMPTY 0
# define ADD 1

# define T 0
# define R 1
# define G 2
# define B 3

# define PARAMS 8

# define DOOR 0
# define PROJECTILE 1
# define SPRITE 2
# define HIT 3

# define DFL_SIZE 20

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

typedef struct s_hit
{
	// info sur la case / l'element touche par le rayon
}							t_hit;

typedef union u_trgb
{
	u_int32_t				hex;
	u_int8_t				trgb[4];
	struct
	{
		u_int8_t			t;
		u_int8_t			red;
		u_int8_t			green;
		u_int8_t			blue;
	};
}							t_color;

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
	double					pdist;
	int						side;
}							t_projectile;

typedef struct s_vector
{
	int						type;
	size_t					size;
	size_t					bsize;
	size_t					index;
	union
	{
		t_door				*d;
		t_projectile		*p;
		t_sprite			*s;
		t_hit				*h;
		size_t				*ul;
		void				*ptr;
	} ptr;
}							t_vector;

typedef struct s_render
{
	t_vector				rhit;
	t_vec					ray_dir;
	t_vec					pray_dir;
	t_vec					side_dist;
	t_vec					pside_dist;
	t_vec					tside_dist;
	t_vec					dside_dist;
	t_vec					delta_dist;
	t_vec					transform;
	t_vec					sprite;
	t_vec					pos;
	t_vec					ppos;
	t_intvec				draw_x;
	t_intvec				draw_y;
	t_intvec				map;
	t_vec					dmap;
	t_vec					pmap;
	t_intvec				step;
	t_vec					dstep;
	t_intvec				draw;
	t_intvec				pdraw;
	t_intvec				tdraw;
	t_intvec				ddraw;
	t_intvec				tex;
	t_intvec				ptex;
	t_intvec				dtex;
	t_intvec				pwtex;
	t_intvec				pixel;
	double					camera_x;
	double					pdist;
	double					ppdist;
	double					tpdist;
	double					dpdist;
	double					texpos;
	double					dtexpos;
	double					ptexpos;
	double					pwtexpos;
	double					mystep;
	double					dmystep;
	double					pmystep;
	double					pwmystep;
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
	int						lh;
	int						plh;
	int						tlh;
	int						dlh;
	int						id;
	int						did;
	int						pid;
	int						pwid;
	int						twidth;
	int						dtwidth;
	int						ptwidth;
	int						pwtwidth;
	int						s;
	int						ds;
	int						ps;
	int						pws;
	int						portal;
	int						vpos;
}							t_render;

typedef struct s_weapon
{
	int						type;
	int						state;
	t_texture				*texture;
}							t_weapon;

typedef struct s_player
{
	t_weapon				weapon;
	t_vec					pos;
	t_vec					dir;
	t_vec					p;
	t_vec					speed;
	t_vec					delta_dist;
	t_vec					side_dist;
	t_intvec				look_pos;
	t_intvec				step;
	t_intvec				map;
	double					pdist;
	bool					looking;
	int						looking_side;
	double					jump;
	int						jumping;
	int						y;
}							t_player;

typedef struct s_map
{
	t_vec					s_pos;
	char					**map;
	char					s_dir;
	t_color					c_color;
	t_color					f_color;
}							t_map;

typedef struct s_screen
{
	void					*img;
	char					*addr;
	int						bpp;
	int						ll;
	int						endian;
}							t_screen;

typedef struct s_mlx
{
	void					*mlx;
	void					*win;
	int						width;
	int						height;
}							t_mlx;

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
	double					ztbuffer[WIDTH][HEIGHT];
	t_map					map;
	t_player				p;
	t_mlx					mlx;
	t_texture				wt[WTEXTURES];
	t_texture				st[STEXTURES];
	t_texture				ptextures[PTEXTURES];
	t_screen				screen;
	// t_render				r;
	t_vector				sprites;
	t_vector				doors;
	t_vector				projectiles;
	char					*files[WTEXTURES];
	int						timeframes[WTEXTURES];
	char					*sfiles[STEXTURES];
	char					*pfiles[PTEXTURES];
	int						colors_c[4];
	int						colors_f[4];
	pthread_mutex_t			state_m;
	pthread_mutex_t			rendered_m[THREADS];
	int						rendered[THREADS];
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
int							on_mouse_move(int x, int y, void *param);
int							on_mouse_click(int button, int x, int y,
								void *param);
// int						logic_loop(void *param);

/*Engine*/
void						ft_draw(t_game *game, const int w, const int dx,
								t_render *r);
void						ft_drawmap(t_game *game);
void						ft_drawsprites(t_game *game, const int x,
								const int dx);
void						ft_wall(const t_game *game, t_render *r);
void						ft_dwall(const t_game *game, t_render *r);
void						ft_drawwallpixel(const t_game *game, const int x,
								const int y, t_render *r);
void						ft_ddrawpixel(t_game *game, const int x,
								const int y, t_render *r);
void						*ft_thread(void *arg);
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
void						ft_pwall(const t_game *game, t_render *r);
void						ft_pdrawpixel(t_game *game, const int x,
								const int y, t_render *r);
int							ft_loop(void *param);
int							ft_init_mlx(t_game *g);
void						ft_start(t_game *game);
void						ft_handle_movement(t_game *g);
void						ft_handle_aim(t_game *g);
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
long						ft_atoi(const char *str);
int							max(int a, int b);
char						**ft_split(char const *s, char c);
int							create_trgb(int t, int r, int g, int b);
void						put_colors(t_game *game);
void						ft_swapi(int *a, int *b);
void						ft_swapd(double *a, double *b);
int							ft_outside(const t_game *game, const int x,
								const int y);
int							ft_create_vector(t_vector *vector, int type,
								size_t size);
void						ft_add_to_vector(t_vector *vec, void *ptr);
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
