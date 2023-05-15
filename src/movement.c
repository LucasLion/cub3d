/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/15 16:58:41 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

	c = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(c->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		c->player->is_moving = 1;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		c->player->is_moving = 2;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		c->player->is_moving = 3;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		c->player->is_moving = 4;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		c->player->is_moving = 5;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		c->player->is_moving = 6;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
}

void	check_movement(t_cub *c)
{
	if (c->player->is_moving == 1)
	{
		c->player->img->instances[0].y -= 1;
		c->player->line->instances[0].y -= 1;
	}
	else if (c->player->is_moving == 2)
	{
		c->player->img->instances[0].x -= 1;
		c->player->line->instances[0].x -= 1;
	}
	else if (c->player->is_moving == 3)
	{
		c->player->img->instances[0].y += 1;
		c->player->line->instances[0].y += 1;
	}
	else if (c->player->is_moving == 4)
	{
		c->player->img->instances[0].x += 1;
		c->player->line->instances[0].x += 1;
	}
	if (c->player->is_moving == 5)
	{
		c->player->ang -= 0.1;
		if (c->player->ang < 0)
			c->player->ang += (2 * PI);
	}
	else if (c->player->is_moving == 6)
	{
		c->player->ang += 0.1;
		if (c->player->ang > (2 * PI))
			c->player->ang -= (2 * PI);
	}
}

void	ft_hook(void *param)
{
	t_cub *c;

	c = param;
	check_movement(c);
	draw_line(c, c->player->img->instances[0].x, c->player->img->instances[0].y);
}
