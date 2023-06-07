/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 13:14:29 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	press_key(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

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
	if (keydata.key == MLX_KEY_SPACE)
		c->player->is_moving |= 0x40;
}

void	release_key(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

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
	if (keydata.key == MLX_KEY_SPACE)
		c->player->is_moving &= ~0x40;
}

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

	c = param;
	if (keydata.action == MLX_RELEASE && keydata.key == MLX_KEY_SPACE)
		toggle_door(c->player->p_pos.x, c->player->p_pos.y, c);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(c->mlx);
	if (keydata.action == MLX_PRESS)
		press_key(keydata, param);
	if (keydata.action == MLX_RELEASE)
		release_key(keydata, param);
}

int	check_collision(float x, float y, t_cub *c)
{
	int	j;
	int	i;

	j = x / c->tilesize;
	i = y / c->tilesize;
	if (c->map[i][j] == '1' || c->map[i][j] == '2')
		return (0);
	return (1);
}
