/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:19:12 by adel-sol          #+#    #+#             */
/*   Updated: 2021/03/01 13:03:49 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>

# define ERROR						-1
# define SUCCESS					1
# define TRUE						1
# define FALSE						0
# define SPEED						0.07
# define S_SPEED					0.04
# define HORIZ						2
# define VERTI						3
# define SPRITES					8
# define INTERUPT					-2
# define NO_INSEC					-13
# define RED_1						0xCF0C0C
# define RED_2						0x9C0C0C
# define RED_3						0x740909
# define RED_4						0x590707
# define PURPLE_1					0xa3009e
# define PURPLE_2					0x8a0085
# define PURPLE_3					0x70006c
# define PURPLE_4					0x52014f
# define BORDER_HUD					0x000000
# define FILE_HEADER_SIZE			14
# define INFO_HEADER_SIZE			40
# define HEAL						0.4
# define DMG						0.05
# define MAX_FRME					12
# define MAX_ANIM					7
# define FRME_FREQ					0.13
# define LIFE_NUM					20
# define GAME_ON					1
# define END_GAME					2
# define LIFE_BAR_NAME				"./.data/hud/life"
# define FINAL_SCENE				"./.data/final_scene.xpm"
# define GAME_OVER					"./.data/game_over.xpm"
# define HEART						'a'
# define MUSHROOM					'4'
# define FINISH						'5'
# define ANTIDOTE					'b'

typedef struct		s_resolution
{
	int				x;
	int				y;
	int				check;
}					t_resolution;

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
}					t_point;

typedef struct		s_ln
{
	t_point			a;
	t_point			b;
}					t_ln;

typedef struct		s_pl
{
	t_ln			*h;
	t_ln			*v;
	int				hl;
	int				vl;
}					t_pl;

typedef struct		s_player
{
	t_point			ang;
	t_point			sov;
	t_point			pos;
	float			life;
	short			poisoned;
}					t_player;

typedef struct		s_img
{
	void			*img;
	int				*data;
	int				height;
	int				width;
	int				check;
}					t_img;

typedef struct		s_textures
{
	t_img			north;
	t_img			south;
	t_img			east;
	t_img			west;
	t_img			sprite[SPRITES];
	t_img			life_bar[LIFE_NUM];
}					t_textures;

typedef struct		s_anim
{
	t_img			frame[MAX_FRME];
	short			f_num;
}					t_anim;

typedef struct		s_line
{
	char			*line;
	int				len;
	struct s_line	*next;
}					t_line;

typedef struct		s_map
{
	char			**content;
	int				height;
	int				width;
}					t_map;

typedef struct		s_idx
{
	int				i;
	int				j;
	int				k;
}					t_idx;

typedef struct		s_angle
{
	double			vis_h;
	double			vis_v;
	double			h;
	double			v;
}					t_angle;

typedef struct		s_preproc
{
	t_point			line;
	double			dist;
}					t_preproc;

typedef struct		s_elem
{
	double			x;
	double			y;
	double			z;
	t_img			s;
}					t_elem;

typedef struct		s_stack
{
	t_elem			*sprites;
	t_preproc		*saves;
	int				current;
}					t_stack;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	int				pixel_bits;
	int				line_bytes;
	int				endian;
}					t_mlx;

typedef struct		s_key
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				rot_u;
	int				rot_d;
	int				rot_l;
	int				rot_r;
	int				squat;
}					t_key;

typedef struct		s_config
{
	double			*cos_load;
	double			*sin_load;
	int				fd;
	t_resolution	resolution;
	t_textures		textures;
	int				floor;
	int				check_f;
	int				ceiling;
	int				check_c;
	t_map			map;
	t_player		player;
	t_pl			lines;
	t_angle			angle;
	int				*im_data;
	void			*img;
	t_mlx			mlx;
	t_point			base;
	t_key			key;
	int				bmth;
	int				ray_idx;
	t_anim			animation[MAX_ANIM];
	float			a_frame;
	int				game_state;
	time_t			rawtime;
	time_t			secc;
	short			game_time;
}					t_config;

int					skip_spaces(char *line);
int					set_resolution(char *line, t_config *cfg);
int					set_texture(char *line, char four_dir, \
					t_config *cfg, int *count);
int					set_fc_color(char *line, char fc, t_config *cfg);
int					get_map(char *line, t_line **map, char *interupt);
int					save_map(t_line *map, t_config *cfg);
int					valid_map_check(t_config *cfg, int single_player);
int					parse_all_params(char *file_path, t_config *cfg);
void				ft_lst_back(t_line **alst, t_line *new);
int					ft_sizelst(t_line *lst);
int					get_max_width(t_line *lst);
int					free_map_onerr(t_map *map, t_line **lines, int i);
void				lst_free_elem(t_line *elem);
void				print_matrix(t_config *cfg);
t_line				*ft_lastlst(t_line *lst);
int					print_error(char *msg);
int					create_trgb(int t, int r, int g, int b);
int					get_t(int trgb);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);
t_point				rot_z(t_point sov, double a, t_config *cfg);
int					ft_close(t_config *cfg, int tofree);
int					key_press(int keycode, t_config *cfg);
int					free_config(t_config *cfg, int code);
int					build_lines(t_config *cfg);
int					print_frame(t_config *cfg);
t_point				wall_intersection(t_config *cfg, t_point vec, \
					t_stack *stk);
int					check_insec(t_point *insec, t_config *cfg, \
					t_point dif, t_stack *stk);
void				move_player(t_config *cfg, double speed);
void				rotate_camera(t_config *cfg);
int					set_image(t_mlx *mlx, t_img *img, char *path);
int					key_release(int keycode, t_config *cfg);
int					do_action(t_config *cfg);
void				sprite_pixel(t_point center, t_config *cfg, \
					t_point insec, t_stack *stk);
double				line_slope(t_point a, t_point b);
void				stack_sort(t_stack *stk);
int					stack_push(t_stack *stk, t_elem elem);
t_elem				stack_head(t_stack *stk);
t_elem				stack_pop(t_stack *stk);
int					stack_isempty(t_stack stk);
double				two_points_dist(t_point a, t_point b);
void				print_sprites(t_config *cfg, t_stack *stk, \
					t_idx a, t_point insec);
t_point				get_vec(t_point first, t_point second);
void				sprite_precision(t_config *cfg, t_idx *a, t_idx t, \
					t_elem sprite);
void				double_print(int res_width, int *image, int color);
int					set_animation(char *line, t_config *cfg, int count);
int					create_bitmap(t_config *cfg);
int					game_over(t_config *cfg);
int					get_life_bar(t_config *cfg);
int					check_cub_extension(char *path);
int					end_game(t_config *cfg);
int					colision(t_config *cfg, float x, float y);
void				pre_frame_setup(t_config *cfg, t_stack *stk, int *x);
int					cos_sin_load(t_config *cfg);
void				init_main_img(t_config *cfg);
void				print_hud(t_config *cfg);
void				timer_tick(t_config *cfg);
void				squat(t_config *cfg);
void				init_params(t_config *cfg);
int					check_duplicate_textures(t_config *cfg, char x, int n);
int					check_existing_object(t_config *cfg, t_idx c);
int					check_minimum_data(t_config *cfg);
int					count_split_elems(char **s);
t_point				rot_90(t_point sov);
int					m_wall(char x);
int					m_white_space(char x);
int					m_fixed_chars(char x);
int					m_sp_nl(char x);
int					m_player_pos(char x);
int					m_s_2_9(char x);
int					m_anim(char x);
int					m_is_sprite(char x);
int					m_solid_sprite(char x);
int					m_map_valid_characters(char x);

#endif
