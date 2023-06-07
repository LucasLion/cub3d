/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:15:02 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 09:09:38 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../libft/include/libft.h"
#include "../include/MLX42.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include "MLX42.h"

#define PI 3.14159
#define DEFINITION 8
#define DEPTH 1.7
#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 600
#define SPEED 6

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_rays
{
	float 				ang;
	double				len;
	t_point				wall;
	char				dir;
	long unsigned int	color;	
	int					door;
	int					v_door;
	int					h_door;
}				t_rays;


typedef struct	s_textures
{
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	unsigned long	floor;
	unsigned long	ceiling;
	int				nb_elems;
}				t_textures;

typedef struct	s_player
{
	t_point			p_pos;
	t_point			m_pos;
	float			player_x_dif;
	float			player_y_dif;
	int				is_moving;
	float			ang;
	float			speed;
	mlx_texture_t	**texture;
	mlx_image_t		*img;
	}				t_player;

typedef struct	s_cub
{
	int					screen_width;
	int					screen_height;
	int					map_width;
	int					map_height;
	int					tilesize;
	int					tilesize_2d;
	int					true_screen_width;
	int					view_ang;
	mlx_t				*mlx;
	char				**map;
	long unsigned int	color;
	t_textures			*t;	
	mlx_texture_t		**textures;
	mlx_image_t			*i_door;
	mlx_texture_t		*t_door;
	int					nb_line_map_start;
	int					line_H;
	t_point				start;
	t_point				end;
	t_point				pix;
	long unsigned int	color_pix;
	float 				ty_step;
	t_player			*player;
	mlx_image_t			*img2d;
	mlx_image_t			*img3d;
	t_rays				*rays;
	
}				t_cub;

int				ft_error(char *str);
int				get_nb_lines_in_map_file(int fd, char **argv);
int				get_nb_line_map_start(char **f, t_cub *c);
char			**get_file(char **argv);
char			**get_description(char **map);
char			**get_map(char **file, int i);
t_textures		*get_textures(t_cub *c, char **file);
int				free_function(char **file, t_cub *c);
int				init_cub(t_cub *c, char **file);

/* ----------- PARSING ----------- */

int		parse_infos(char **infos, t_cub *c);
int		parse_elems_in_map(char **map);
int		parsing(char **file, t_cub *c);
int		parse_borders(char **map);
int		parse_number_players(char **map);
int		parse_file(int argc, char **argv);
int		map_width(char **map);


/* ----------- DISPLAY ----------- */

void		put_square(t_cub *c, int x, int y, long int color);
int			display_2d_map(t_cub *c);
int			display_3d_map(t_cub *c);
t_player	*init_player(t_cub *c);

/* ----------- MOVEMENT ----------- */

void		move_player(mlx_key_data_t keydata, void *param);
void		check_movement(t_cub *c);
void		ft_hook(void *param);
int			player_out(t_cub *c);
void		open_door(float i, float j, t_cub *c);


/* ----------- LINE----------- */

void 		draw_line(t_cub *c, int x, int y);
void 		draw_one_line(t_cub *cub, mlx_image_t *image, t_point start, t_point end, long unsigned int c);
void 		draw_one_line_3d(mlx_image_t *image, t_point start, t_point end);
int			wall_or_empty(t_cub *c, int x , int y);
void 		draw_rays(t_cub *c);

/* ----------- FIND PIXEL ----------- */

unsigned long int find_color_pixel(t_cub *c, int i, int l_h, int p);
unsigned long get_color_pixel(mlx_texture_t *texture, int x_texture, int y_texture);
unsigned long int get_color_v2(mlx_texture_t *t, int pixel );
unsigned long int get_pixel_north(t_cub *c, int i, int l_h, int p);

/* ----------- RAYS ----------- */

void check_horizontal(t_cub *c, t_point *start, t_point *end, int ray);
void check_vertical(t_cub *c, t_point *start, t_point *end, int ray);
void vert_or_hor(t_cub *c, int i);
t_point	reduce_point(t_point p, t_cub *c);

/* ----------- ANIMATIONS ----------- */

int				animation(t_cub *c);
mlx_texture_t	**load_animation(t_cub *c);
mlx_image_t		*load_image(t_cub *c, int x);
void			draw_anim(t_cub *c, int x);
mlx_texture_t	*load_texture_anim(t_cub *c, int x);

#endif
