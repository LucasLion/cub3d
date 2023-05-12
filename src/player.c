/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:06:29 by llion             #+#    #+#             */
/*   Updated: 2023/05/12 16:05:21 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_player	*init_player(t_cub *c, int i, int j)
{
	t_player	*player;
	mlx_image_t	*img;

	player = ft_calloc(1, sizeof(t_player));
	img = mlx_new_image(c->mlx, c->tilesize, c->tilesize);
	if (!player->img || (mlx_image_to_window(c->mlx, player->img, j * c->tilesize, i * c->tilesize) < 0))
		return NULL;
	player->x_start = i;
	player->y_start = j;
	return (player);
}
