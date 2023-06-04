/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/04 11:49:26 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void draw_one_line(t_cub *c, mlx_image_t *image, t_point start, t_point end, long unsigned int color)
{
	float				delta_y;
	float				delta_x;
	int					length;
	
	delta_y = end.y - start.y;
	delta_x = end.x - start.x;
	length = sqrt((delta_y * delta_y) + (delta_x * delta_x)) + 1;
	delta_x /= length;
	delta_y /= length;
	{
		while(length)
		{
			if (((start.x < (c->map_width * c->tilesize_H) - 1) &&  start.x > 0) \
					&& (start.y < ((c->map_height * c->tilesize_V) - 1) && start.y > 0))
				mlx_put_pixel(image, start.x, start.y, color); 
			start.y += delta_y;
			start.x += delta_x;
			--length;
		}
	}
}

void	set_struct_ray_H(t_cub *c, int i, t_point wall_hit, double len_ray)
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
}

void	set_struct_ray_V(t_cub *c, int i, t_point wall_hit, double len_ray)
{
	c->rays[i].len = len_ray;
	c->rays[i].color = 0x00ff00ff;
	c->rays[i].wall.x = wall_hit.x;
	c->rays[i].wall.y = wall_hit.y;
	c->rays[i].dir = 'E';
	if (c->rays[i].ang > PI / 2 && c->rays[i].ang  < PI / 2 * 3)
	{
		c->rays[i].color = 0xff00ffff;
		c->rays[i].dir = 'W'; 
	}
}

void vert_or_hor(t_cub *c, int i)
{
	t_point	end_v;
	t_point	end_h;
	double	vlen;
	double	hlen;
	t_point p;

	p = c->player->p_pos;
	check_horizontal(c, &p, &end_h, c->rays[i].ang);
	check_vertical(c, &p, &end_v, c->rays[i].ang);
	vlen = sqrt(((end_v.y - p.y)* (end_v.y - p.y)) + ((end_v.x - p.x) * (end_v.x - p.x)));
	hlen = sqrt(((end_h.y - p.y)* (end_h.y - p.y)) + ((end_h.x - p.x) * (end_h.x - p.x)));
	if (hlen <= vlen)
	{
		draw_one_line(c, c->img2d, reduce_point(p, c), reduce_point(end_h, c), 0xff0000ff);
		set_struct_ray_H(c, i, end_h, hlen);
	}
	else 
	{
		draw_one_line(c, c->img2d, reduce_point(p, c),reduce_point(end_v, c), 0xff0000ff);
		set_struct_ray_V(c, i, end_v, vlen);
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

void draw_rays(t_cub *c)
{
	int i;
	float one_deg;

	i = 0;
	one_deg = 0.0174 / DEFINITION;
	c->rays[i].ang = c->player->ang - (c->view_ang / 2 * one_deg);
	if (c->img2d)
		mlx_delete_image(c->mlx, c->img2d);
	c->img2d = mlx_new_image(c->mlx, c->tilesize_H_2d * c->map_width , c->tilesize_V_2d * c->map_height);
	if (!c->img2d || (mlx_image_to_window(c->mlx, c->img2d, 0, 0) < 0))
		return ;
	while (i < c->view_ang)
	{
		if (i != 0)
			c->rays[i].ang = c->rays[i - 1].ang + one_deg;
		if (c->rays[i].ang  >= 2 * PI)
			c->rays[i].ang -= 2 * PI;
		else if (c->rays[i].ang  < 0)
			c->rays[i].ang  += (2 * PI);
		vert_or_hor(c, i);
		fish_eye(c, i);
		i++;
	}
}
