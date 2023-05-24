/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/24 16:39:10 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void draw_one_line(t_cub *c, mlx_image_t *image, t_point start, t_point end, long unsigned color)
{
	float				delta_y;
	float				delta_x;
	long long int		length;
	
	delta_y = end.y - start.y;
	delta_x = end.x - start.x;
	length = sqrt((delta_y * delta_y) + (delta_x * delta_x));
	delta_x /= length;
	delta_y /= length;
	{
		while(length)
		{
			if ((start.x < (c->screen_width - 1) &&  start.x > 0) \
					&& (start.y < (c->screen_height - 1) && start.y > 0))
				mlx_put_pixel(image, start.x, start.y, color); 
			start.y += delta_y;
			start.x += delta_x;
			--length;
		}
	}
}

void check_horizontal(t_cub *c, t_point *start, t_point *end, float ang)
{
	t_point offset;
	float	ra = ang;
	float	atan = -1 / tan(ra);
	int dof = 0;
	
	if (ra > PI) 
	{
		end->y = (int)(start->y /c->tilesize_V) * c->tilesize_V + c->tilesize_V;
		end->x = ((end->y - start->y) * atan) + start->x;
		offset.y = c->tilesize_V;
		offset.x = (offset.y * atan);	
	}
	if (ra < PI) 
{
		end->y = ((int)(start->y /c->tilesize_V) * c->tilesize_V - 0.001);
		end->x = (end->y - start->y) * atan + start->x;
		offset.y = - c->tilesize_V;
		offset.x = (offset.y * atan);	
	}
	while (dof < c->map_height)
	{
		if (end->y >= 0 && end->y < c->screen_height / 2 && end->x >= 0 && end->x < c->screen_width )
		{
			int i = end->y / c->tilesize_V;
			int j = end->x / c->tilesize_H;
			if (i < 0 || j <  0  || i > c->map_height || j > c->map_width || (c->map[i][j] == '1') )
			{
				dof = c->map_height;
				break;
			}
			else	
			{
				end->x += offset.x;
				end->y += offset.y;
				dof++;
			}
		}
		else	
		{
			dof = c->map_height;
			break;
		}
	}
}
void check_vertical(t_cub *c, t_point *start, t_point *end, float ang)
{
	t_point offset;
	float	ra = ang;
	float	ntan = -tan(ra);
	int dof = 0;
	
	if (ra > (PI / 2) && ra < (PI / 2 * 3)) 
	{
		end->x = (int)(start->x /c->tilesize_H) * c->tilesize_H - 0.001;
		end->y = ((end->x - start->x) * ntan) + start->y;
		offset.x = - c->tilesize_H;
		offset.y = (offset.x * ntan);	
	}
	if (ra < (PI /2) || (ra > PI / 2 * 3)) 
	{
		end->x = ((int)(start->x /c->tilesize_H) * c->tilesize_H + c->tilesize_H);
		end->y = (end->x - start->x) * ntan + start->y;
		offset.x = c->tilesize_H;
		offset.y = (offset.x * ntan);	
	}
	while (dof < (c->map_width))
	{
		if (end->y >= 0 && end->y < c->screen_height / 2 && end->x >= 0 && end->x < c->screen_width)
		{
			int i = end->y / c->tilesize_V;
			int j = end->x / c->tilesize_H;
			if (i < 0 || j <  0  || i > c->map_height || j > c->map_width || (c->map[i][j] == '1') )
			{
				dof = c->map_width;
				break;
			}
			else	
			{
				end->x += offset.x;
				end->y += offset.y;
				dof++;
			}
		}
		else	
		{
			dof = c->map_width;
			break;
		}
	}
}

void draw_one_ray(t_cub *c, float ang, int i)
{
	t_point	end_v;
	t_point	end_h;
	double	vlen;
	double	hlen;
	t_point p;

	p = c->player->p_pos;
	check_horizontal(c, &p, &end_h, ang);
	check_vertical(c, &p, &end_v, ang);
	vlen = sqrt(((end_v.y - p.y)* (end_v.y - p.y)) + ((end_v.x - p.x) * (end_v.x - p.x)));
	hlen = sqrt(((end_h.y - p.y)* (end_h.y - p.y)) + ((end_h.x - p.x) * (end_h.x - p.x)));
	if (hlen <= vlen)
	{
		draw_one_line(c, c->img2d, p, end_h, 0xff0000ff);
		c->rays_len[i] = hlen;
	}
	else 
	{
		draw_one_line(c, c->img2d, p, end_v, 0xff0000ff);
		c->rays_len[i] = vlen;
	}
}

void	fish_eye(t_cub *c, float ang, int i)
{
	float	diff;

	diff = c->player->ang - ang;
	if (diff < 0)
		diff += 2 * PI;
	if (diff > 2 * PI)
		diff -= 2 * PI;
	c->rays_len[i] = c->rays_len[i] * cos(diff) * 0.8;
}

void draw_rays(t_cub *c)
{
	int i;
	float ang;
	float one_deg;

	i = 0;
	one_deg = 0.0174 / 2 / 2 / 2;
	//one_deg = 0.0054;
	ang = c->player->ang - (c->view_ang / 2 * one_deg);
	if (c->img2d)
		mlx_delete_image(c->mlx, c->img2d);
	c->img2d = mlx_new_image(c->mlx, c->screen_width , c->screen_height / 2);
	if (!c->img2d || (mlx_image_to_window(c->mlx, c->img2d, 0, c->screen_height / 2) < 0))
		return ;
	while (i < c->view_ang)
	{
		if (ang >= 2 * PI)
			ang -= 2 * PI;
		else if (ang < 0)
			ang += (2 * PI);
		draw_one_ray(c, ang, i);
		fish_eye(c, ang, i);
		ang += one_deg;
		i++;
	}
}
