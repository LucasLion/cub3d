/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/06/12 15:52:05 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	map_width(char **map)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	return (width - 1);
}

void	draw_rectangle(mlx_image_t *img, int y_start, int y_end,
		unsigned long int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->width)
	{
		j = y_start;
		while (j < y_end)
		{
			mlx_put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	init(t_cub *c)
{
	mlx_image_t	*img;

	img = mlx_new_image(c->mlx, c->true_screen_width - 1, SCREEN_HEIGHT - 1);
	draw_rectangle(img, 0, SCREEN_HEIGHT / 2, c->t->ceiling);
	draw_rectangle(img, SCREEN_HEIGHT / 2, img->height, c->t->floor);
	if (!img || (mlx_image_to_window(c->mlx, img, 0, 0)) < 0)
		return ;
	img->instances[0].z = 0;
	display_2d_map(c);
	init_player(c);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_key_hook(c->mlx, &move_player, c);
	mlx_loop_hook(c->mlx, &ft_hook, c);
	mlx_loop(c->mlx);
	mlx_terminate(c->mlx);
}

int	main(int argc, char **argv)
{
	char	**file;
	t_cub	*c;

	c = ft_calloc(1, sizeof(t_cub));
	file = 0;
	if (parse_file(argc, argv) != 0)
		file = get_file(argv);
	else
	{
		free_function(file, c);
		return (-1);
	}
	if (init_cub(c, file) == 0)
	{
		free_function(file, c);
		return (-1);
	}
	if (parsing(file, c) == 0)
	{
		free_function(file, c);
		return (-1);
	}
	init(c);
	free_function(file, c);
	return (0);
}
