/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/06/03 13:04:14 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int get_color(mlx_texture_t *t, int pixel )
{
	int r = t->pixels[pixel];
	int g = t->pixels[pixel +1];
	int b = t->pixels[pixel +2];
	int a = t->pixels[pixel +3];
	return (r << 24 | g << 16 | b << 8 | a );
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
	c->img3d = mlx_new_image(c->mlx, c->true_screen_width, c->true_screen_height);
	if (!c->img3d || (mlx_image_to_window(c->mlx, c->img3d, 0, 0) < 0))
		return 0;
	c->img3d->instances[0].z = 0;
	mlx_key_hook(c->mlx, &move_player, c);
	mlx_loop_hook(c->mlx, &ft_hook, c);
	mlx_loop(c->mlx);
	mlx_terminate(c->mlx);
	free_function(file, c);
	return (0);
}
