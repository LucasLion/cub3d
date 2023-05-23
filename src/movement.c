/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/23 13:09:49 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	press_key(mlx_key_data_t keydata, void *param)
{
	t_cub *c;

	c = param;
		if (keydata.key == MLX_KEY_W)
			c->player->is_moving |= 0x01;
		if (keydata.key == MLX_KEY_S)
			c->player->is_moving |= 0x04;
		if (keydata.key == MLX_KEY_S)
			c->player->is_moving |= 0x04;
		if (keydata.key == MLX_KEY_A)
			c->player->is_moving |= 0x02;
		if (keydata.key == MLX_KEY_D)
			c->player->is_moving |= 0x08;
		if (keydata.key == MLX_KEY_RIGHT)
			c->player->is_moving |= 0x10;
		if (keydata.key == MLX_KEY_LEFT)
			c->player->is_moving |= 0x20;
}

void	release_key(mlx_key_data_t keydata, void *param)
{
	t_cub *c;

	c = param;
	if (keydata.key == MLX_KEY_W)
		c->player->is_moving &= ~0x01;
	if (keydata.key == MLX_KEY_S)
		c->player->is_moving &= ~0x04;
	if (keydata.key == MLX_KEY_A)
		c->player->is_moving &= ~0x02;
	if (keydata.key == MLX_KEY_D)
		c->player->is_moving &= ~0x08;
	if (keydata.key == MLX_KEY_RIGHT)
		c->player->is_moving &= ~0x10;
	if (keydata.key == MLX_KEY_LEFT)
		c->player->is_moving &= ~0x20;
}

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

	c = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(c->mlx);
	if (keydata.action == MLX_PRESS)
		press_key(keydata, param);
	if (keydata.action == MLX_RELEASE)
		release_key(keydata, param);
}

void	check_movement(t_player *p)
{
	if (p->is_moving & 0x01)
	{
		p->p_pos.x += cos(p->ang);
		p->p_pos.y += -sin(p->ang);
	}
	else if (p->is_moving == 0x02)
	{
		p->p_pos.x -= -cos(p->ang + (PI / 2));
		p->p_pos.y -= sin(p->ang + (PI / 2));
	}
	else if (p->is_moving & 0x04)
	{
		p->p_pos.x -= cos(p->ang);
		p->p_pos.y -= -sin(p->ang);
	}
	else if (p->is_moving & 0x08)
	{
		p->p_pos.x += cos(p->ang - (PI / 2));
		p->p_pos.y += -sin(p->ang - (PI / 2));
	}
	if (p->is_moving & 0x10)
	{
		p->ang -= 0.04;
		if (p->ang < 0)
			p->ang += (2 * PI);
	}
	else if (p->is_moving & 0x20)
	{
		p->ang += 0.04;
		if (p->ang > (2 * PI))
			p->ang -= (2 * PI);
	}
}

void	ft_hook(void *param)
{
	t_cub *c;

	c = param;
	check_movement(c->player);
	draw_rays(c);
	display_3d_map(c);
}
