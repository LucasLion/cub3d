/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:15:02 by llion             #+#    #+#             */
/*   Updated: 2023/05/12 16:37:20 by amouly           ###   ########.fr       */
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
#include "MLX42.h"
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

typedef struct	s_player
{
	int			x_start;
	int			y_start;
	mlx_image_t	*img;

}				t_player;

typedef struct	s_cub
{
	int			screen_width;
	int			screen_height;
	int			map_width;
	int			map_height;
	int			tilesize;
	mlx_t		*mlx;
	char		**map;
	t_textures	*t;	
	int			nb_line_map_start;
	t_player	*player;
}				t_cub;

int		ft_error(char *str);
int		get_nb_lines_in_map_file(int fd);
int	get_nb_line_map_start(char **f, t_cub *c);
char	**get_file();
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

int			display_2d_map(t_cub *c);
void		move_player(mlx_key_data_t keydata, void *param);
t_player	*init_player(t_cub *c, int i, int j);

#endif
