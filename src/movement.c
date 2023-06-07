/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 10:36:41 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mouse_move(t_cub *c)
{
	int	x;
	int y; 

	mlx_get_mouse_pos(c->mlx, &x, &y);
	x -= c->true_screen_width / 2;
	c->player->ang -= ((float)x / 400);
	if (c->player->ang < 0)
			c->player->ang += (2 * PI);
	if (c->player->ang > 2 * PI)
			c->player->ang -= (2 * PI);
	mlx_set_mouse_pos(c->mlx, c->true_screen_width / 2, SCREEN_HEIGHT / 2);
}

void	toggle_door(float i, float j, t_cub *c)
{
	int	k;
	int l;
	t_point		futur_pos;

	futur_pos.x = c->player->p_pos.x + cos(c->player->ang) * SPEED * 15;
	futur_pos.y = c->player->p_pos.y - (sin(c->player->ang) * SPEED * 15);
	k = futur_pos.x / c->tilesize;
	l = futur_pos.y / c->tilesize;
	if (c->map[l][k] == '2')
		c->map[l][k] = '3';
	else if (c->map[l][k] == '3')
		c->map[l][k] = '2';
}

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
		if (keydata.key == MLX_KEY_SPACE)
			c->player->is_moving |= 0x40;
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

int check_collision(float x, float y, t_cub *c)
{
	int j;
	int i;

	j = x / c->tilesize;
	i = y / c->tilesize;
	if (c->map[i][j] == '1' || c->map[i][j] == '2')
		return (0);
	return (1);
}

void check_W(t_cub	*c)
{
	t_point		futur_pos;

	futur_pos.x = c->player->p_pos.x + cos(c->player->ang) * SPEED * 10;
	futur_pos.y = c->player->p_pos.y - (sin(c->player->ang) * SPEED * 10);
	if (check_collision(futur_pos.x, c->player->p_pos.y, c))
		c->player->p_pos.x += cos(c->player->ang) * SPEED;
	if (check_collision(c->player->p_pos.x, futur_pos.y, c))
		c->player->p_pos.y -= sin(c->player->ang) * SPEED;
}

void check_S(t_cub	*c)
{
	t_point		futur_pos;

	futur_pos.x = c->player->p_pos.x - cos(c->player->ang) * SPEED * 10;
	futur_pos.y = c->player->p_pos.y + (sin(c->player->ang) * SPEED * 10);
	if (check_collision(futur_pos.x, c->player->p_pos.y, c))
		c->player->p_pos.x -= cos(c->player->ang) * SPEED;
	if (check_collision(c->player->p_pos.x, futur_pos.y, c))
		c->player->p_pos.y += sin(c->player->ang) * SPEED;
}

void check_A(t_cub	*c)
{
	t_point		futur_pos;

	futur_pos.x = c->player->p_pos.x + cos(c->player->ang + (PI / 2)) * SPEED * 10;
	futur_pos.y = c->player->p_pos.y - sin(c->player->ang + (PI / 2)) * SPEED * 10;
	if (check_collision(futur_pos.x, c->player->p_pos.y, c))
		c->player->p_pos.x += cos(c->player->ang + (PI / 2)) * SPEED;
	if (check_collision(c->player->p_pos.x, futur_pos.y, c))
		c->player->p_pos.y -= sin(c->player->ang + (PI / 2)) * SPEED;
}

void check_D(t_cub	*c)
{
	t_point		futur_pos;

	futur_pos.x = c->player->p_pos.x + cos(c->player->ang - (PI / 2)) * SPEED * 10;
	futur_pos.y = c->player->p_pos.y - sin(c->player->ang - (PI / 2)) * SPEED * 10;
	if (check_collision(futur_pos.x, c->player->p_pos.y, c))
		c->player->p_pos.x += cos(c->player->ang - (PI / 2)) * SPEED;
	if (check_collision(c->player->p_pos.x, futur_pos.y, c))
		c->player->p_pos.y -= sin(c->player->ang - (PI / 2)) * SPEED;
}

void	check_movement(t_cub *c)
{
	if (c->player->is_moving & 0x01)
		check_W(c);
	else if (c->player->is_moving & 0x04)
		check_S(c);
	if (c->player->is_moving & 0x02)
		check_A(c);
	else if (c->player->is_moving & 0x08)
		check_D(c);
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

int	player_out(t_cub *c)
{
	if (c->player->p_pos.x <= 0 || c->player->p_pos.y <= 0 \
		|| c->player->p_pos.x >= c->tilesize * c->map_width || c->player->p_pos.y >= c->tilesize * c->map_height)
		return (ft_error("YOU WENT OFF OF THE MAP YOU FOOL!!\nVANISH NOW..."));
	return (1);
}

void	ft_hook(void *param)
{
	t_cub *c;

	c = param;
	animation(c);
	check_movement(c);
	mouse_move(c);
	draw_rays(c);
	display_3d_map(c);
	player_out(c);
}
