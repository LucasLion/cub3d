/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:15:02 by llion             #+#    #+#             */
/*   Updated: 2023/05/23 17:04:41 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "../libft/include/libft.h"
#include "../include/MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include "MLX42.h"
#define PI 3.14159
//#include "MLX42_Int.h"
//#include "MLX42_input.h"

typedef struct	s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	int		nb_elems;
}				t_textures;

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_player
{
	t_point		p_pos;
	t_point		m_pos;
	float		player_x_dif;
	float		player_y_dif;
	int			is_moving;
	float		ang;
	int			speed;

}				t_player;

typedef struct	s_cub
{
	int			screen_width;
	int			screen_height;
	int			map_width;
	int			map_height;
	int			tilesize;
	int			view_ang;
	mlx_t		*mlx;
	char		**map;
	double		*rays_len;
	t_textures	*t;	
	int			nb_line_map_start;
	t_player	*player;
	mlx_image_t	*img2d;
	mlx_image_t	*img3d;
	
}				t_cub;

int		ft_error(char *str);
int		get_nb_lines_in_map_file(int fd, char **argv);
int		get_nb_line_map_start(char **f, t_cub *c);
char	**get_file(char **argv);
char	**get_description(char **map);
char	**get_map(char **file, int i);

/* ----------- PARSING ----------- */

int		parse_infos(char **infos, t_cub *c);
int		parse_elems_in_map(char **map);
int		parsing(char **file, t_cub *c);
int		parse_borders(char **map);
int		parse_number_players(char **map);
int		parse_file(int argc, char **argv);


/* ----------- DISPLAY ----------- */

void		put_square(t_cub *c, int x, int y, long int color);
int			display(t_cub *c);
int			display_2d_map(t_cub *c);
int			display_3d_map(t_cub *c);
t_player	*init_player(t_cub *c);

/* ----------- MOVEMENT ----------- */

void		move_player(mlx_key_data_t keydata, void *param);
void		check_movement(t_player *c);
void		ft_hook(void *param);
void		collision(t_cub *c, t_player *p);


/* ----------- LINE----------- */

void 		draw_line(t_cub *c, int x, int y);
void 		draw_one_line(mlx_image_t *image, t_point start, t_point end, long unsigned int c);
void 		draw_one_line_3d(mlx_image_t *image, t_point start, t_point end);
int			wall_or_empty(t_cub *c, int x , int y);
void 		draw_rays(t_cub *c);

#endif
