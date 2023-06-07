/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_check2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:46:22 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 14:32:08 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	offset_increase(t_point offset, t_point *end, int *k)
{
	end->x += offset.x;
	end->y += offset.y;
	(*k)++;
}

void	set_special_h(t_cub *c, int i, int j, int ang)
{
	if (c->map[i][j] == '2')
		c->rays[ang].h_special = 1;
	if (c->map[i][j] == 'P')
		c->rays[ang].h_special = 2;
}

void	set_special_v(t_cub *c, int i, int j, int ang)
{
	if (c->map[i][j] == '2')
		c->rays[ang].v_special = 1;
	if (c->map[i][j] == 'P')
		c->rays[ang].v_special = 2;
}
