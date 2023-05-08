/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:15:02 by llion             #+#    #+#             */
/*   Updated: 2023/05/08 15:58:36 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "../libft/include/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct	s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*fl;
	char	*cl;	

	int		lines_before_map;
}				t_textures;

int		get_nb_lines_in_map_file(int fd, char **argv);
char	**get_file(int argc, char **argv);
char	**get_description(char **map, t_textures *t);
char	**get_map(char **map, t_textures *t);

/* ----------- PARSING ----------- */

int		parse_infos(char **infos, t_textures *t);
int		parse_elems(char **map);
int		parsing(char **file);
int		parse_borders(char **map);
int		parse_number_players(char **map);
int		parse_file(int argc, char **argv);

/* ----------- ERRORS ----------- */

int		ft_error();

#endif
