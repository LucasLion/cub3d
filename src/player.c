/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:06:29 by llion             #+#    #+#             */
/*   Updated: 2023/05/22 11:24:17 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray_images(mlx_image_t **rays)
{
	int i;

	i = 0;
	while(i < 60)
	{
		rays[i] = NULL;
		i++;
	}
}

t_player	*init_player(t_cub *c, int i, int j)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	player->img = mlx_new_image(c->mlx, c->tilesize, c->tilesize);
	player->rays = ft_calloc(60, sizeof(mlx_image_t));
	init_ray_images(c->player->rays);
	player->x_pos = i;
	player->y_pos = j;
	player->ang = 0;
	if (c->map[i][j] == 'N')
		player->ang = PI / 2;
	else if (c->map[i][j] == 'S')
		player->ang = PI / 2 * 3 ;
	else if (c->map[i][j] == 'W')
		player->ang = PI;
	return (player);
	
	c->test = 0;
}
