/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/05/17 13:05:59 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (0);
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
	c->tilesize = 50;
	c->nb_line_map_start = get_nb_line_map_start(file, c);
	c->t->nb_elems = 0;
	c->map = get_map(file, c->nb_line_map_start);
	if (!c->map)
		return (ft_error("Empty file"));
	c->map_height = ft_tablen(c->map) * c->tilesize;
	c->map_width = map_width(c->map) * c->tilesize;
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
	display_2d_map(c);
	put_player_square(c, c->player->x_pos, c->player->y_pos);
	c->player->line = NULL;
	draw_line(c, c->player->img->instances[0].x, c->player->img->instances[0].y);
	mlx_key_hook(c->mlx, &move_player, c);
	mlx_loop_hook(c->mlx, &ft_hook, c);
	mlx_loop(c->mlx);
	free_function(file, c);
	return (0);
}
