/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/05/29 17:01:19 by amouly           ###   ########.fr       */
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
	c->t = get_textures(file);
	c->color = 0xdc6400ff;
	//c->text_wall = ft_calloc(1, sizeof(mlx_texture_t));
	//c->text_wall = NULL;
	c->text_wall = mlx_load_png("./bricksx64.png");
	c->view_ang = 60 * DEFINITION ;
	c->nb_line_map_start = get_nb_line_map_start(file, c);
	c->t->nb_elems = 0;
	c->map = get_map(file, c->nb_line_map_start);
	c->rays_len = ft_calloc(c->view_ang, sizeof(double));
	c->color_tab = ft_calloc(c->view_ang, sizeof(long unsigned int));
	if (!c->map)
		return (ft_error("Empty file"));
	c->map_height = ft_tablen(c->map);
	c->map_width = map_width(c->map);
	c->tilesize_V = SCREEN_HEIGHT / c->map_height;
	c->tilesize_V_2d = c->tilesize_V / 8;
	c->tilesize_H = SCREEN_WIDTH / c->map_width;
	c->tilesize_H_2d = c->tilesize_H / 8;
	c->mlx = mlx_init(SCREEN_WIDTH - (SCREEN_WIDTH % c->map_width), SCREEN_HEIGHT - (SCREEN_HEIGHT % c->map_height), "CUB3D", true);
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
	printf ("largeur texture : %d\n", c->text_wall->width);
	printf ("hauteur texture : %d", c->text_wall->height);
	mlx_image_t *new;
	new = mlx_new_image(c->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	int i = 0;
	while (i < 64)
	{
		int j = 0;
		while (j < 64)
		{
			int pixel =  (i * 64) + (j * 4);
			printf ("pixel = %d\n", pixel);
			uint8_t	red = c->text_wall->pixels[pixel];
			printf("red : %d\n", c->text_wall->pixels[pixel]);
			uint8_t	green = c->text_wall->pixels[pixel + 1];
			printf("green : %d\n", c->text_wall->pixels[pixel+1]);
			uint8_t	blue = c->text_wall->pixels[pixel + 2];
			printf("blue : %d\n", c->text_wall->pixels[pixel+2]);
			uint8_t	transp = c->text_wall->pixels[pixel + 3];
			printf("alpha : %d\n", c->text_wall->pixels[pixel+3]);
			mlx_put_pixel(new, i , j ,rgb_to_hexa(red, green, blue, transp ));
			j++;	
		}
		i ++;
	}
	if (!new || (mlx_image_to_window(c->mlx, new, 50 , 400 ))< 0)
		return (1) ;
	new->instances[0].z = 1;
	mlx_key_hook(c->mlx, &move_player, c);
	mlx_loop_hook(c->mlx, &ft_hook, c);
	mlx_loop(c->mlx);
	mlx_terminate(c->mlx);
	mlx_delete_texture(c->text_wall);
	free_function(file, c);
	return (0);
}
