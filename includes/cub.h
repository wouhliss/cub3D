/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:46:02 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 23:49:47 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx.h"
# include <fcntl.h>
# include <ft_dprintf.h>
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

# define PI 3.141592653589793f
# define HALF_PI 1.57079632679f

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

# define TP 0
# define TB 1

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
#  define THREADS 1
# endif
# define W 1280
# define HW 640
# define T_WIDTH 1280
# define HEIGHT 720
# define HALF_HEIGHT 360
# define MW 320
# define MH 180
# define MX 80
# define MY 20
# define MS 3
# define MPR 4
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

# define PARAMS 6

# define DOOR 0
# define PROJECTILE 1
# define SPRITE 2
# define HIT 3

# define DFL_SIZE 4

# define CUBES 21
# define GLASS 18

# define WEAPONS 3
# define SPRITES 2

typedef unsigned int		t_ui;

typedef struct s_texture
{
	void					*img;
	char					*a;
	int						bpp;
	int						ll;
	int						endian;
	int						height;
	int						w;
	int						frames;
	int						f;
	int						s;
	time_t					last;
}							t_texture;

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
	time_t					last;
	double					frame;
	bool					delete;
}							t_door;

typedef struct s_sprite		t_sprite;
typedef struct s_projectile	t_projectile;

typedef struct s_sprite
{
	t_vec					pos;
	t_vec					dir;
	t_vec					plane;
	int						t;
	int						vr;
	int						hr;
	int						vpos;
	double					vdiff;
	int						hide;
	bool					delete;
	bool					collision;
}							t_sprite;

typedef struct s_projectile
{
	t_sprite				*sprite;
	int						t;
	bool					delete;
	t_vec					dd;
	t_vec					sd;
	t_intvec				m;
	t_intvec				step;
	double					pdist;
	int						side;
}							t_projectile;

typedef struct s_hit		t_hit;

typedef struct s_vector
{
	int						t;
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
		void				*u_ptr;
	} u_ptr;
}							t_vector;

typedef struct s_render
{
	t_vec					ray_dir;
	t_vec					sd;
	t_vec					dd;
	t_vec					t;
	t_vec					sp;
	t_vec					sp2;
	t_vec					tsp;
	t_vec					pos;
	t_intvec				draw_x;
	t_intvec				draw_y;
	t_intvec				m;
	t_intvec				step;
	t_intvec				draw;
	t_intvec				tex;
	t_intvec				linetex;
	t_intvec				ptex;
	t_intvec				p;
	double					camera_x;
	double					pdist;
	double					texpos;
	double					linepos;
	double					ptexpos;
	double					mystep;
	double					linestep;
	double					pmystep;
	double					ind;
	double					shift;
	int						spritewidth;
	int						sph;
	int						spsx;
	int						hit;
	int						side;
	int						lh;
	int						id;
	int						pid;
	int						twidth;
	int						ptwidth;
	int						s;
	int						ps;
	int						vpos;
	char					c;
}							t_render;

typedef struct s_hit
{
	t_render				render;
}							t_hit;

typedef struct s_weapon
{
	int						t;
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
	t_vec					dd;
	t_vec					sd;
	t_intvec				look_pos;
	t_intvec				step;
	t_intvec				m;
	double					pdist;
	bool					looking;
	int						looking_side;
	double					jump;
	int						jumping;
	double					y;
}							t_player;

typedef struct s_map
{
	t_vec					s_pos;
	char					**m;
	char					s_dir;
	t_color					cc;
	t_color					fc;
}							t_map;

typedef struct s_screen
{
	void					*img;
	char					*a;
	int						bpp;
	int						ll;
	int						endian;
	double					lratio;
	double					rratio;
}							t_screen;

typedef struct s_mlx
{
	void					*mlx;
	void					*win;
	int						w;
	int						height;
}							t_mlx;

typedef struct s_portal
{
	t_intvec				pos;
	t_vec					dir;
	t_vec					plane;
	int						side;
}							t_portal;

typedef struct s_game		t_game;

typedef struct s_thread
{
	t_game					*g;
	int						id;
	pthread_t				tid;
	t_vector				hit;
	int						dx;
	int						x;
	double					zbuffer[T_WIDTH][HEIGHT];
	t_ui					tbuffer[T_WIDTH][HEIGHT];
	double					tdbuffer[T_WIDTH][HEIGHT];
}							t_thread;

typedef struct s_game
{
	t_map					m;
	t_player				p;
	t_mlx					mlx;
	t_texture				wt[WTEXTURES];
	t_texture				st[STEXTURES];
	t_texture				pt[PTEXTURES];
	t_texture				gt[GLASS];
	char					dfl_a[4];
	t_texture				dfl;
	t_screen				s;
	t_vector				sprites;
	t_vector				doors;
	t_vector				pls;
	t_thread				threads[THREADS];
	char					*files[WTEXTURES];
	int						wframes[WTEXTURES];
	char					*sfiles[STEXTURES];
	int						sframes[STEXTURES];
	char					*pfiles[PTEXTURES];
	int						colors_c[4];
	int						colors_f[4];
	int						rendered[THREADS];
	t_portal				pl;
	t_portal				pr;
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
	int						w;
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
void						ft_update_doors_portals(t_game *g);
void						ft_portal(const t_game *game, t_render *r);
void						ft_truc(const t_game *game, t_render *r);
void						ft_portal_hit(t_thread *t, const t_game *g,
								t_render *r);
void						ft_handle_pls(t_game *g);
void						ft_drawppixel(t_thread *t, const int x, const int y,
								t_render *r);
bool						ft_can_move(t_game *g, const double x,
								const double y);
void						ft_remove_door(t_game *g, t_door *door);
bool						ft_check_doors(t_game *g, const double x,
								const double y);
void						ft_update_door(t_game *g, t_door *door);
void						ft_drawsprites(t_thread *t);
void						ft_drawtpixel(t_thread *t, const int x, const int y,
								t_render *r);
void						ft_hitcalc(const t_game *g, t_render *r,
								const int t);
void						ft_drawhit(t_thread *t, t_render *r);
void						*ft_draw(void *p);
void						ft_drawmap(t_game *game);
void						ft_wall(const t_game *game, t_render *r);
void						ft_door(const t_game *game, t_render *r);
void						ft_drawwallpixel(t_game *game, const int x,
								const int y, t_render *r);
void						ft_drawdoorpixel(t_thread *t, const int x,
								const int y, t_render *r);
void						ft_drawspixel(t_thread *t, const int x, const int y,
								t_render *r);
void						ft_drawhitrow(t_thread *t, const int x);
int							ft_loop(void *param);
int							ft_init_mlx(t_game *g);
void						ft_start(t_game *game);
void						ft_handle_movement(t_game *g);
void						ft_handle_aim(t_game *g);
bool						ft_check_doors(t_game *g, double x, double y);
char						ft_get_block(t_game *g);
void						ft_glass(const t_game *game, t_render *r);
void						ft_add_projectile(t_game *g, t_vec pos, t_vec dir,
								int t);
void						*ft_hit(const t_game *g, t_render *r, t_thread *t);
void						ft_steps(const t_game *g, t_render *r);
void						ft_dda(const t_game *g, t_render *r, t_thread *t);
void						ft_rays(const t_game *g, t_render *r, const int x,
								t_thread *t);
void						ft_portal_1(t_render *r, const t_game *g);
void						ft_portal_2(t_render *r, const t_game *g);
void						ft_portal_3(t_render *r, const t_game *g);
void						ft_portal_4(t_render *r, const t_game *g);
void						ft_portal_l(const t_game *g, t_render *r,
								t_hit *hit);
void						ft_portal_r(const t_game *g, t_render *r,
								t_hit *hit);
void						ft_psteps(t_projectile *p);
void						ft_pdda(t_game *game, t_projectile *p);
bool						ft_candelete(t_game *game, double x, double y);
bool						ft_oob(t_game *game, double x, double y);
bool						ft_projectile_hit(t_game *g, t_projectile *p);
void						my_mlx_pixel_tput(const t_screen *data, const int x,
								const int y, unsigned int color);
bool						ft_can_step(t_game *g, t_sprite *s);
void						ft_portal_sprite(t_game *g, t_thread *t);
void						ft_animate(t_game *g);
void						ft_check_door(t_game *g);
void						ft_place_sprite(t_game *g);
int							ft_get_glass_id(const char c);
/*Parsing*/

void						init_map(char *path, t_game *game);
void						get_info_map(t_game *game);
int							set_colors(char *line, t_game *game);
void						pre_format_map(t_game *game);
void						format_map(t_game *game);
int							check_map(t_game *game);
int							set_texture(char *line, t_game *game);
/*Utils*/
bool						ft_valid_color(const char *str);
int							ic(char *charset, char c);
char						*get_next_line(int fd);
int							ft_strnchr(t_buffer *buffer);
char						*ft_strchr(char *s, int c);
char						*ft_strrchr(char *s, int c);
int							ft_dprintf(int fd, const char *str, ...);
int							ft_strcmp(const char *s1, const char *s2);
char						*ft_strdup(const char *s);
char						**join_tab(char **m, char *str);
int							ft_strlen(const char *str);
char						**ft_copy(char **m);
int							plen(char **m);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
void						*ft_calloc(size_t nmemb, size_t size);
void						skip_spaces(char *line, int *i);
int							plen(char **m);
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
void						ft_create_vector(t_vector *vector, int t,
								size_t size);
void						*ft_add_to_vector(const t_game *g, t_vector *vec,
								void *u_ptr);
void						*ft_resize_dvector(t_vector *vector);
void						*ft_resize_pvector(t_vector *vector);
void						*ft_resize_svector(const t_game *g,
								t_vector *vector);
void						*ft_resize_hvector(t_vector *vector);
t_intvec					ft_get_facing_int(const int side, t_intvec vec);
t_vec						ft_get_facing(const int side, t_vec vec);
t_vec						ft_side_to_plane(const int side);
t_vec						ft_side_to_dir(const int side);
void						ft_import_portals(t_game *g, const char **pt);
void						ft_import_glass(t_game *g, const char **gt);
void						ft_import_sprites(t_game *g);
bool						ft_check_walls(t_game *g);
bool						ft_check_sprites(t_game *g);
/*Garbage collector*/

void						*gc(void *u_ptr, int i);
void						ft_close_fd(bool to_close, int new_fd);

/*Free and exit*/

void						panic(const char *message);
void						free_tab(char **tab);

#endif
