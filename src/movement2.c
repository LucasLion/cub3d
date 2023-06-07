/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 15:25:20 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_w(t_cub *c)
{
	t_point	futur_pos;

	futur_pos.x = c->player->p_pos.x + cos(c->player->ang) * SPEED * 10;
	futur_pos.y = c->player->p_pos.y - (sin(c->player->ang) * SPEED * 10);
	if (check_collision(futur_pos.x, c->player->p_pos.y, c))
		c->player->p_pos.x += cos(c->player->ang) * SPEED;
	if (check_collision(c->player->p_pos.x, futur_pos.y, c))
		c->player->p_pos.y -= sin(c->player->ang) * SPEED;
}

void	check_s(t_cub *c)
{
	t_point	futur_pos;

	futur_pos.x = c->player->p_pos.x - cos(c->player->ang) * SPEED * 10;
	futur_pos.y = c->player->p_pos.y + (sin(c->player->ang) * SPEED * 10);
	if (check_collision(futur_pos.x, c->player->p_pos.y, c))
		c->player->p_pos.x -= cos(c->player->ang) * SPEED;
	if (check_collision(c->player->p_pos.x, futur_pos.y, c))
		c->player->p_pos.y += sin(c->player->ang) * SPEED;
}

void	check_a(t_cub *c)
{
	t_point	futur_pos;

	futur_pos.x = c->player->p_pos.x + cos(c->player->ang + (PI / 2)) * SPEED
		* 5;
	futur_pos.y = c->player->p_pos.y - sin(c->player->ang + (PI / 2)) * SPEED
		* 5;
	if (check_collision(futur_pos.x, c->player->p_pos.y, c))
		c->player->p_pos.x += cos(c->player->ang + (PI / 2)) * SPEED;
	if (check_collision(c->player->p_pos.x, futur_pos.y, c))
		c->player->p_pos.y -= sin(c->player->ang + (PI / 2)) * SPEED;
}

void	check_d(t_cub *c)
{
	t_point	futur_pos;

	futur_pos.x = c->player->p_pos.x + cos(c->player->ang - (PI / 2)) * SPEED
		* 5;
	futur_pos.y = c->player->p_pos.y - sin(c->player->ang - (PI / 2)) * SPEED
		* 5;
	if (check_collision(futur_pos.x, c->player->p_pos.y, c))
		c->player->p_pos.x += cos(c->player->ang - (PI / 2)) * SPEED;
	if (check_collision(c->player->p_pos.x, futur_pos.y, c))
		c->player->p_pos.y -= sin(c->player->ang - (PI / 2)) * SPEED;
}

void	check_movement(t_cub *c)
{
	if (c->player->is_moving & 0x01)
		check_w(c);
	else if (c->player->is_moving & 0x04)
		check_s(c);
	if (c->player->is_moving & 0x02)
		check_a(c);
	else if (c->player->is_moving & 0x08)
		check_d(c);
	if (c->player->is_moving & 0x10)
	{
		c->player->ang -= 0.04;
		if (c->player->ang < 0)
			c->player->ang += (2 * PI);
	}
	else if (c->player->is_moving & 0x20)
	{
		c->player->ang += 0.04;
		if (c->player->ang > (2 * PI))
			c->player->ang -= (2 * PI);
	}
}
