/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/02 15:12:29 by amouly           ###   ########.fr       */
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

int check_collision(t_point future_pos, t_cub *c)
{
	int j;
	int i;

	j = future_pos.x / c->tilesize_H;
	i = future_pos.y / c->tilesize_V;
	if (c->map[i][j] == '1')
		return (0);
	else
		return (1);
}




void	check_movement(t_player *p, t_cub *c)
{
	t_point	futur_pos;
	
	if (p->is_moving & 0x01)
	{
	futur_pos.x = p->p_pos.x + cos(p->ang) * SPEED * 10;
		futur_pos.y = p->p_pos.y - (sin(p->ang) * SPEED * 10);
		if (check_collision(futur_pos, c))
		{
			p->p_pos.x += cos(p->ang) * SPEED;
			p->p_pos.y -= sin(p->ang) * SPEED;
		}
	}
	else if (p->is_moving & 0x04)
	{
		futur_pos.x = p->p_pos.x - cos(p->ang) * SPEED * 10;
		futur_pos.y = p->p_pos.y + sin(p->ang) * SPEED * 10;
		if (check_collision(futur_pos, c))
		{
			p->p_pos.x -= cos(p->ang) * SPEED;
			p->p_pos.y += sin(p->ang) * SPEED;
		}
	}
	if (p->is_moving & 0x02)
	{
		futur_pos.x = p->p_pos.x + cos(p->ang + (PI / 2)) * SPEED * 10;
		futur_pos.y = p->p_pos.y - sin(p->ang + (PI / 2)) * SPEED * 10;
		if (check_collision(futur_pos, c))
		{
			p->p_pos.x += cos(p->ang + (PI / 2)) * SPEED;
			p->p_pos.y -= sin(p->ang + (PI / 2)) * SPEED;
		}
	}
	else if (p->is_moving & 0x08)
	{		
		futur_pos.x = p->p_pos.x + cos(p->ang - (PI / 2)) * SPEED * 10;
		futur_pos.y = p->p_pos.y - sin(p->ang - (PI / 2)) * SPEED * 10;
		if (check_collision(futur_pos, c))
		{
			p->p_pos.x += cos(p->ang - (PI / 2)) * SPEED;
			p->p_pos.y -= sin(p->ang - (PI / 2)) * SPEED;
		}
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

int	player_out(t_cub *c)
{
	if (c->player->p_pos.x <= 0 | c->player->p_pos.y <= 0 | c->player->p_pos.x >= SCREEN_WIDTH | c->player->p_pos.y >=SCREEN_HEIGHT)
		return (ft_error("YOU WENT OFF OF THE MAP YOU FOOL!!\nVANISH NOW..."));
	return (1);
}

void	ft_hook(void *param)
{
	t_cub *c;

	c = param;
	check_movement(c->player, c);
	draw_rays(c);
	//display_3d_map(c);
	player_out(c);
}
