/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/22 12:21:16 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	press_key(mlx_key_data_t keydata, void *param)
{
	t_cub *c;

	c = param;
		if (keydata.key == MLX_KEY_W)
			c->player->is_moving |= 0x01;
		else if (keydata.key == MLX_KEY_A)
			c->player->is_moving |= 0x02;
		else if (keydata.key == MLX_KEY_S)
			c->player->is_moving |= 0x04;
		else if (keydata.key == MLX_KEY_D)
			c->player->is_moving |= 0x08;
		else if (keydata.key == MLX_KEY_RIGHT)
			c->player->is_moving |= 0x10;
		else if (keydata.key == MLX_KEY_LEFT)
			c->player->is_moving |= 0x20;
}

void	release_key(mlx_key_data_t keydata, void *param)
{
	t_cub *c;

	c = param;
	if (keydata.key == MLX_KEY_W)
		c->player->is_moving &= ~0x01;
	else if (keydata.key == MLX_KEY_A)
		c->player->is_moving &= ~0x02;
	else if (keydata.key == MLX_KEY_S)
		c->player->is_moving &= ~0x04;
	else if (keydata.key == MLX_KEY_D)
		c->player->is_moving &= ~0x08;
	else if (keydata.key == MLX_KEY_RIGHT)
		c->player->is_moving &= ~0x10;
	else if (keydata.key == MLX_KEY_LEFT)
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

void	check_movement(t_cub *c)
{
	if (c->player->is_moving & 0x01)
	{
		//c->player->img->instances[0].y -= 1;
		//c->player->line->instances[0].y -= 1;
		c->player->img->instances[0].x += c->player->player_x_dif * 0.005;
		c->player->img->instances[0].y += c->player->player_y_dif * 0.005;
	}
	// A et D ok
	else if (c->player->is_moving == 2)
	{
		c->player->img->instances[0].x -= 1;
	}
	else if (c->player->is_moving & 0x04)
	{
		//c->player->img->instances[0].y += 1;
		//c->player->line->instances[0].y += 1;
		c->player->img->instances[0].x -= c->player->player_x_dif * 0.005;
		c->player->img->instances[0].y -= c->player->player_y_dif * 0.005;
	}
	else if (c->player->is_moving & 0x08)
	{
		c->player->img->instances[0].x += 1;
	}
	if (c->player->is_moving & 0x10)
	{
		c->player->ang -= 0.01;
		c->player->player_x_dif = cosf(c->player->ang) * 40;
		c->player->player_y_dif = - sinf(c->player->ang) * 40;
		if (c->player->ang < 0)
			c->player->ang += (2 * PI);
	}
	else if (c->player->is_moving & 0x20)
	{
		c->player->ang += 0.01;
		c->player->player_x_dif = cosf(c->player->ang) * 40;
		c->player->player_y_dif = - sinf(c->player->ang) * 40;
		if (c->player->ang > (2 * PI))
			c->player->ang -= (2 * PI);
	}
}


void	ft_hook(void *param)
{
	t_cub *c;

	c = param;
	check_movement(c);
	//draw_line(c, c->player->img->instances[0].x, c->player->img->instances[0].y);
	draw_rays(c, c->player->img->instances[0].x, c->player->img->instances[0].y);
	printf ("ang : %f\n", c->player->ang);
	printf ("deviation x and y : %f et %f\n", c->player->player_x_dif, c->player->player_y_dif);
	
}
