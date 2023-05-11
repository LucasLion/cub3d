/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:15:02 by llion             #+#    #+#             */
/*   Updated: 2023/05/11 13:46:26 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "../libft/include/libft.h"
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
	char	**map;
	int		nb_elems;
}				t_textures;

typedef struct	s_game
{
	int					map_height;
	int					map_width;
	int					x_player;
	int					y_player;
	char				**map;
	
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_texture_t		*texture;
}				t_game;

int		ft_error(char *str);
int		get_nb_lines_in_map_file(int fd);
char	**get_file();
char	**get_description(char **map);
int		get_map(char **map, t_textures *t, int i);

/* ----------- PARSING ----------- */

int		parse_infos(char **infos, t_textures *t);
int		parse_elems_in_map(char **map);
int		parsing(char **file, t_textures *t);
int		parse_borders(char **map);
int		parse_number_players(char **map);
int		parse_file(int argc, char **argv);

/* ----------- ADD GRAPHIC ----------- */

int		add_graphic(t_game *g);

#endif
