/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:06:29 by llion             #+#    #+#             */
/*   Updated: 2023/05/22 14:02:09 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_player	*init_player(t_cub *c, int i, int j)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	player->img = mlx_new_image(c->mlx, c->tilesize, c->tilesize);
	player->x_pos = i;
	player->y_pos = j;
	c->view_ang = 80;
	player->speed = 3;
	if (c->map[i][j] == 'E')
		player->ang = 0;
	else if (c->map[i][j] == 'N')
		player->ang = PI / 2;
	else if (c->map[i][j] == 'S')
		player->ang = PI / 2 * 3 ;
	else if (c->map[i][j] == 'W')
		player->ang = PI;
	return (player);
	
	c->test = 0;
}
