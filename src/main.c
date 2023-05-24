/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/05/24 17:08:45 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_error(char *str)
{
	printf("%s\nExiting...\n", str);
	exit(EXIT_FAILURE);
}

int	free_function(char **file, t_cub *c)
{
	ft_freetab(file);
	ft_freetab(c->map);
	free(c->t);
	free(c);
	return (0);
}

int	map_width(char **map)
{
	int	i;
	int	width;

	i = 0;
	width = 0 ;
	width = ft_strlen(map[i]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	return (width - 1);
}

int	init_cub(t_cub *c, char **file)
{
	c->t = ft_calloc(1, sizeof(t_textures));
	c->view_ang = 60 * 2 * 2 * 2 ;
	c->nb_line_map_start = get_nb_line_map_start(file, c);
	c->t->nb_elems = 0;
	c->map = get_map(file, c->nb_line_map_start);
	c->rays_len = ft_calloc(c->view_ang, sizeof(double));
	if (!c->map)
		return (ft_error("Empty file"));
	c->map_height = ft_tablen(c->map);
	c->map_width = map_width(c->map);
	//c->tilesize = 40;
	//c->screen_height = c->map_height * c->tilesize;
	//c->screen_width = c->map_width * c->tilesize;
	c->screen_height = SCREEN_HEIGHT;
	c->screen_width = SCREEN_WIDTH;
	c->tilesize_V = SCREEN_HEIGHT / c->map_height;
	c->tilesize_H = SCREEN_WIDTH / c->map_width;
	c->mlx = mlx_init(c->screen_width, c->screen_height, "CUB3D", true);
	c->player = ft_calloc(1, sizeof(t_player));
	if (!c->mlx)
		return (ft_error("MLX failed"));
	return (1);
}


int	main(int argc, char **argv)
{
	char	**file;
	t_cub	*c;

	c = ft_calloc(1, sizeof(t_cub));
	if (parse_file(argc, argv) != 0)
		file = get_file(argv);
	else
		return (-1);
	if (init_cub(c, file) == 0)
		return (-1);
	if (parsing(file, c) == 0)
	{
		free_function(file, c);
		return (-1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	display_2d_map(c);
	init_player(c);
	printf("tilesize H ==> %d et tilesize V  ==> %d\n", c->tilesize_H, c->tilesize_V);
	printf("Player en pixel : x ==> %f et y ==> %f\n", c->player->p_pos.y, c->player->p_pos.x);
	printf("Player en case: x ==> %f et y ==> %f\n", c->player->m_pos.x, c->player->m_pos.y);
	printf("Nombre de cases : largeur ==> %d et haueteur  ==> %d\n", c->map_width, c->map_height);
	mlx_key_hook(c->mlx, &move_player, c);
	mlx_loop_hook(c->mlx, &ft_hook, c);
	mlx_loop(c->mlx);
	mlx_terminate(c->mlx);
	free_function(file, c);
	return (0);
}
