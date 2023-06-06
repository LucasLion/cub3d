/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:06:29 by llion             #+#    #+#             */
/*   Updated: 2023/06/06 14:29:42 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_player	*init_player(t_cub *c)
{
	int			i;
	int			j;

	i = c->player->m_pos.x;
	j = c->player->m_pos.y;
	c->player->p_pos.x = j * c->tilesize + (c->tilesize / 2);
	c->player->p_pos.y = i * c->tilesize + (c->tilesize / 2);
	if (c->map[i][j] == 'E')
		c->player->ang = 0;
	else if (c->map[i][j] == 'N')
		c->player->ang = PI / 2;
	else if (c->map[i][j] == 'S')
		c->player->ang = PI / 2 * 3 ;
	else if (c->map[i][j] == 'W')
		c->player->ang = PI;
	return (c->player);
}
