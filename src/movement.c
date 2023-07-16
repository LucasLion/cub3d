/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/07/16 11:29:16 by llion@student    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mouse_move(t_cub *c)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(c->mlx, &x, &y);
	x -= c->true_screen_width / 2;
	c->player->ang -= ((float)x / 400);
	if (c->player->ang < 0)
		c->player->ang += (2 * PI);
	if (c->player->ang > 2 * PI)
		c->player->ang -= (2 * PI);
	mlx_set_mouse_pos(c->mlx, c->true_screen_width / 2, SCREEN_HEIGHT / 2);
}

void	toggle_door(t_cub *c)
{
	int		k;
	int		l;
	t_point	futur_pos;

	futur_pos.x = c->player->p_pos.x + cos(c->player->ang) * SPEED * 15;
	futur_pos.y = c->player->p_pos.y - (sin(c->player->ang) * SPEED * 15);
	k = futur_pos.x / c->tilesize;
	l = futur_pos.y / c->tilesize;
	if (c->map[l][k] == '2')
		c->map[l][k] = '3';
	else if (c->map[l][k] == '3')
		c->map[l][k] = '2';
}

int	player_out(t_cub *c)
{
	if (c->player->p_pos.x <= 0 || c->player->p_pos.y <= 0
		|| c->player->p_pos.x >= c->tilesize * c->map_width
		|| c->player->p_pos.y >= c->tilesize * c->map_height)
		return (ft_error("YOU WENT OFF OF THE MAP YOU FOOL!!\nVANISH NOW..."));
	if (c->map[(int)(c->player->p_pos.y) / c->tilesize][(int)(c->player->p_pos.x
			/ c->tilesize)] == 'P')
		return (ft_error("PFFFEWWW..... YOU MADE IT  OUT  !!!!!!"));
	return (1);
}

void	ft_hook(void *param)
{
	t_cub	*c;

	c = param;
	animation(c);
	check_movement(c);
	if (c->pause == 0)
		mouse_move(c);
	draw_rays(c);
	display_3d_map(c);
	player_out(c);
}
