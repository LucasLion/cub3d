/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 14:17:14 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_struct_ray_h(t_cub *c, int i, t_point wall_hit, double len_ray)
{
	c->rays[i].len = len_ray;
	c->rays[i].color = c->color;
	c->rays[i].wall.x = wall_hit.x;
	c->rays[i].wall.y = wall_hit.y;
	c->rays[i].dir = 'N';
	if (c->rays[i].ang > PI)
	{
		c->rays[i].color = 0x0000ffff;
		c->rays[i].dir = 'S';
	}
	if (c->rays[i].h_special == 1)
		c->rays[i].special = 1;
	if (c->rays[i].h_special == 2)
		c->rays[i].special = 2;
}

void	set_struct_ray_v(t_cub *c, int i, t_point wall_hit, double len_ray)
{
	c->rays[i].len = len_ray;
	c->rays[i].color = 0x00ff00ff;
	c->rays[i].wall.x = wall_hit.x;
	c->rays[i].wall.y = wall_hit.y;
	c->rays[i].dir = 'E';
	if (c->rays[i].ang > PI / 2 && c->rays[i].ang < PI / 2 * 3)
	{
		c->rays[i].color = 0xff00ffff;
		c->rays[i].dir = 'W';
	}
	if (c->rays[i].v_special == 1)
		c->rays[i].special = 1;
	if (c->rays[i].v_special == 2)
		c->rays[i].special = 2;
}

void	vert_or_hor(t_cub *c, int i)
{
	t_point	end_v;
	t_point	end_h;
	double	vlen;
	double	hlen;
	t_point	p;

	p = c->player->p_pos;
	check_horizontal(c, &p, &end_h, i);
	check_vertical(c, &p, &end_v, i);
	vlen = sqrt(((end_v.y - p.y) * (end_v.y - p.y)) + ((end_v.x - p.x)
				* (end_v.x - p.x)));
	hlen = sqrt(((end_h.y - p.y) * (end_h.y - p.y)) + ((end_h.x - p.x)
				* (end_h.x - p.x)));
	if (hlen <= vlen)
	{
		draw_one_line(c, c->img2d, reduce_point(p, c), reduce_point(end_h, c));
		set_struct_ray_h(c, i, end_h, hlen);
	}
	else
	{
		draw_one_line(c, c->img2d, reduce_point(p, c), reduce_point(end_v, c));
		set_struct_ray_v(c, i, end_v, vlen);
	}
}
