/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:50:12 by llion             #+#    #+#             */
/*   Updated: 2023/06/06 17:40:05 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_error(char *str)
{
	printf("%s\nExiting...\n", str);
	exit(EXIT_FAILURE);
}

void cursor(t_cub *c)
{
	mlx_texture_t *t;
	mlx_win_cursor_t *cursor;

	t = mlx_load_png(c->t->NO);
	cursor = mlx_create_cursor(t);
	mlx_set_cursor_mode(c->mlx, MLX_MOUSE_HIDDEN);
}

int	free_function(char **file, t_cub *c)
{
	if (c->t != NULL)
	{
		mlx_delete_texture(c->textures[0]);
		mlx_delete_texture(c->textures[1]);
		mlx_delete_texture(c->textures[2]);
		mlx_delete_texture(c->textures[3]);
	}
	ft_freetab(file);
	if (c->map)
		ft_freetab(c->map);
	free(c->t);
	free(c);
	return (0);
}

void init_cub_2(t_cub *c)
{
	c->map_height = ft_tablen(c->map);
	c->map_width = map_width(c->map);
	c->view_ang = 60 * DEFINITION;
	c->tilesize = 64;
	c->tilesize_2d = c->tilesize / 8;
	if (SCREEN_WIDTH < c->view_ang * 1.5)
		c->true_screen_width = c->view_ang;
	else if (SCREEN_WIDTH < c->view_ang * 2.5 &&  SCREEN_WIDTH >= c->view_ang * 1.5)
		c->true_screen_width = c->view_ang * 2;
	else if (SCREEN_WIDTH < c->view_ang * 3.5 &&  SCREEN_WIDTH >= c->view_ang * 2.5)
		c->true_screen_width = c->view_ang * 3;
	else
		c->true_screen_width = c->view_ang * 4;
}



int	init_cub(t_cub *c, char **file)
{
	c->nb_line_map_start = get_nb_line_map_start(file, c);
	c->t = get_textures(c, file);
	if (c->t == NULL)
		return (0);
	c->textures = ft_calloc(5, sizeof(mlx_texture_t *));
	c->textures[0] = mlx_load_png(c->t->NO);
	c->textures[1] = mlx_load_png(c->t->SO);
	c->textures[2] = mlx_load_png(c->t->WE);
	c->textures[3] = mlx_load_png(c->t->EA);
	c->textures[4] = mlx_load_png("./textures/door.png");
	c->t->nb_elems = 0;
	c->map = get_map(file, c->nb_line_map_start);
	init_cub_2(c);
	c->rays = ft_calloc(c->view_ang, sizeof(t_rays));
	if (!c->map)
		return (ft_error("Empty file"));
	c->mlx = mlx_init(c->true_screen_width, SCREEN_HEIGHT, "CUB3D", true);
	c->player = ft_calloc(1, sizeof(t_player));
	cursor(c);
	if (!c->mlx)
		return (ft_error("MLX failed"));
	return (1);
}

