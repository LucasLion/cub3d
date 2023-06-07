/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 14:30:57 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_one_line(t_cub *c, mlx_image_t *image, t_point start, t_point end)
{
	float	delta_y;
	float	delta_x;
	int		length;

	delta_y = end.y - start.y;
	delta_x = end.x - start.x;
	length = sqrt((delta_y * delta_y) + (delta_x * delta_x)) + 1;
	delta_x /= length;
	delta_y /= length;
	{
		while (length)
		{
			if (((start.x < (c->map_width * c->tilesize) - 1) && start.x > 0)
				&& (start.y < ((c->map_height * c->tilesize) - 1)
					&& start.y > 0))
				mlx_put_pixel(image, start.x, start.y, 0xff0000ff);
			start.y += delta_y;
			start.x += delta_x;
			--length;
		}
	}
}

void	fish_eye(t_cub *c, int i)
{
	float	diff;

	diff = c->player->ang - c->rays[i].ang;
	if (diff < 0)
		diff += 2 * PI;
	if (diff > 2 * PI)
		diff -= 2 * PI;
	c->rays[i].len = c->rays[i].len * cos(diff);
}

void	loop_rays(t_cub *c, float one_deg, int *i)
{
	if (*i != 0)
		c->rays[*i].ang = c->rays[*i - 1].ang + one_deg;
	if (c->rays[*i].ang >= 2 * PI)
		c->rays[*i].ang -= 2 * PI;
	else if (c->rays[*i].ang < 0)
		c->rays[*i].ang += (2 * PI);
	c->rays[*i].special = 0;
	c->rays[*i].h_special = 0;
	c->rays[*i].v_special = 0;
	vert_or_hor(c, *i);
	fish_eye(c, *i);
	(*i)++;
}

void	draw_rays(t_cub *c)
{
	int		i;
	float	one_deg;

	i = 0;
	one_deg = 0.0174 / DEFINITION;
	c->rays[i].ang = c->player->ang - (c->view_ang / 2 * one_deg);
	if (c->img2d)
		mlx_delete_image(c->mlx, c->img2d);
	c->img2d = mlx_new_image(c->mlx, c->tilesize_2d * c->map_width,
			c->tilesize_2d * c->map_height);
	if (!c->img2d || (mlx_image_to_window(c->mlx, c->img2d, 50, 50) < 0))
		return ;
	while (i < c->view_ang)
		loop_rays(c, one_deg, &i);
}
