/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:50:12 by llion             #+#    #+#             */
/*   Updated: 2023/06/02 13:50:30 by llion            ###   ########.fr       */
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
	mlx_delete_texture(c->textures[0]);
	mlx_delete_texture(c->textures[1]);
	mlx_delete_texture(c->textures[2]);
	mlx_delete_texture(c->textures[3]);
	ft_freetab(file);
	ft_freetab(c->map);
	free(c->t);
	free(c);
	return (0);
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

