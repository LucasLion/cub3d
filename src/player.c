/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:06:29 by llion             #+#    #+#             */
/*   Updated: 2023/05/14 15:40:48 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_player	*init_player(t_cub *c, int i, int j)
{
	t_player	*player;
	mlx_image_t	*img;

	player = ft_calloc(1, sizeof(t_player));
	player->img = mlx_new_image(c->mlx, c->tilesize, c->tilesize);
	player->x_pos = i;
	player->y_pos = j;
	player->leng_line = c->tilesize * 0.5;
	player->start_x = (j + 0.4) * c->tilesize;
	player->start_x = (i + 0.4) * c->tilesize;
	player->end_x = player->start_x;
	player->end_y = player->start_y;
	if (c->map[i][j] == 'N')
		player->end_y -= player->leng_line;
	if (c->map[i][j] == 'S')
		player->end_y += player->leng_line;
	if (c->map[i][j] == 'E')
		player->end_x += player->leng_line;
	if (c->map[i][j] == 'W')
		player->end_x -= player->leng_line;
	return (player);
}
