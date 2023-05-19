/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:06:29 by llion             #+#    #+#             */
/*   Updated: 2023/05/19 13:03:02 by amouly           ###   ########.fr       */
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
	player->ang = 0.1;
	if (c->map[i][j] == 'N')
		player->ang = PI / 2 + 0.1;
	//player->ang = PI / 2 * 3;
	else if (c->map[i][j] == 'S')
		player->ang = PI / 2 * 3 + 0.1;
	else if (c->map[i][j] == 'W')
		player->ang = PI + 0.1 ;
	return (player);
	
	c->test = 0;
}
