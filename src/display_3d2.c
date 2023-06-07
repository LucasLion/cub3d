/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 14:22:10 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	special_texture(t_cub *c, int i, mlx_texture_t **t)
{
	if (c->rays[i].special == 1)
		*t = c->textures[4];
	if (c->rays[i].special == 2)
		*t = c->t_exit[c->static_var];
}

void	calculate_pix_x(t_cub *c, int i, mlx_texture_t **t)
{
	if (c->rays[i].dir == 'N' || c->rays[i].dir == 'S')
	{
		*t = c->textures[0];
		c->pix.x = (int)(c->rays[i].wall.x) % c->tilesize;
		if (c->rays[i].ang > PI)
		{
			*t = c->textures[1];
			c->pix.x = (c->tilesize - c->pix.x - 1) * (*t)->width / c->tilesize;
		}
		else
			c->pix.x = c->pix.x * (*t)->width / c->tilesize;
	}
	else
	{
		*t = c->textures[2];
		c->pix.x = (int)(c->rays[i].wall.y) % c->tilesize;
		if (c->rays[i].ang > PI / 2 && c->rays[i].ang < PI / 2 * 3)
		{
			*t = c->textures[3];
			c->pix.x = (c->tilesize - c->pix.x - 1) * (*t)->width / c->tilesize;
		}
		else
			c->pix.x = c->pix.x * (*t)->width / c->tilesize;
	}
	special_texture(c, i, t);
}
