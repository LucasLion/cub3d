/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/06/01 13:22:04 by llion            ###   ########.fr       */
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
	c->nb_line_map_start = get_nb_line_map_start(file, c);
	c->t = get_textures(c, file);
	c->color = 0xdc6400ff;
	c->textures = ft_calloc(4, sizeof(mlx_texture_t *));
	c->textures[0] = mlx_load_png(c->t->NO);
	c->textures[1] = mlx_load_png(c->t->SO);
	c->textures[2] = mlx_load_png(c->t->WE);
	c->textures[3] = mlx_load_png(c->t->EA);
	c->view_ang = 60 * DEFINITION;
	c->t->nb_elems = 0;
	c->map = get_map(file, c->nb_line_map_start);
	c->rays = ft_calloc(c->view_ang, sizeof(t_rays));
	if (!c->map)
		return (ft_error("Empty file"));
	c->map_height = ft_tablen(c->map);
	c->map_width = map_width(c->map);
	c->tilesize_H = SCREEN_WIDTH / c->map_width;
	c->tilesize_V = SCREEN_HEIGHT / c->map_height;
	c->tilesize_V_2d = c->tilesize_V / 8;
	c->tilesize_H_2d = c->tilesize_H / 8;
	c->mlx = mlx_init(SCREEN_WIDTH - (SCREEN_WIDTH % c->map_width), SCREEN_HEIGHT - (SCREEN_HEIGHT % c->map_height), "CUB3D", true);
	c->player = ft_calloc(1, sizeof(t_player));
	if (!c->mlx)
		return (ft_error("MLX failed"));
	return (1);
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
	/*printf ("largeur texture : %d\n", c->text_wall->width);
	printf ("hauteur texture : %d", c->text_wall->height);
	mlx_image_t *new;
	new = mlx_new_image(c->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	int i = 0;
	int pixel = 0;
	int color = 0;
	while (i < c->text_wall->height && i < SCREEN_HEIGHT - 50)
	{
		int j = 0;
		while (j < c->text_wall->width && j < SCREEN_WIDTH - 50)
		{
			color = get_color (c->text_wall, pixel);
			mlx_put_pixel(new, j , i , color );
			pixel += 4;
			j++;	
		}
		i ++;
	}
	if (!new || (mlx_image_to_window(c->mlx, new, 50 , 50))< 0)
		return (1) ;
	new->instances[0].z = 1;*/
	mlx_key_hook(c->mlx, &move_player, c);
	mlx_loop_hook(c->mlx, &ft_hook, c);
	mlx_loop(c->mlx);
	mlx_terminate(c->mlx);
	mlx_delete_texture(c->textures[0]);
	mlx_delete_texture(c->textures[1]);
	mlx_delete_texture(c->textures[2]);
	mlx_delete_texture(c->textures[3]);
	free_function(file, c);
	return (0);
}
