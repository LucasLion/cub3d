/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/23 10:51:55 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void draw_one_line(t_cub *c, t_point start, t_point end)
{
	float			delta_y;
	float			delta_x;
	long long int	length;
	
	delta_y = end.y - start.y;
	delta_x = end.x - start.x;
	length = sqrt((delta_y * delta_y) + (delta_x * delta_x));
	delta_x /= length;
	delta_y /= length;
	while(length)
	{
		mlx_put_pixel(c->player->rays, start.x, start.y, 0xff0456ff); 
		start.y += delta_y;
		start.x += delta_x;
		--length;
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
		end->y = (int)(start->y /c->tilesize) * c->tilesize + c->tilesize;
		end->x = ((end->y - start->y) * atan) + start->x;
		offset.y = c->tilesize;
		offset.x = (offset.y * atan);	
	}
	if (ra < PI) 
	{
		end->y = ((int)(start->y /c->tilesize) * c->tilesize - 0.001);
		end->x = (end->y - start->y) * atan + start->x;
		offset.y = - c->tilesize;
		offset.x = (offset.y * atan);	
	}
	int lim_i = c->map_height / c->tilesize;
	int lim_j = c->map_width / c->tilesize;
	while (dof < lim_i)
	{
		if (end->y >= 0 && end->y < c->map_height && end->x >= 0 && end->x < c->map_width )
		{
			int i = end->y / c->tilesize;
			int j = end->x / c->tilesize;
			if (i < 0 || j <  0  || i > lim_i || j > lim_j || (c->map[i][j] == '1') )
			{
				dof = lim_j;
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
			dof = lim_j;
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
		end->x = (int)(start->x /c->tilesize) * c->tilesize - 0.001;
		end->y = ((end->x - start->x) * ntan) + start->y;
		offset.x = - c->tilesize;
		offset.y = (offset.x * ntan);	
	}
	if (ra < (PI /2) || (ra > PI / 2 * 3)) 
	{
		end->x = ((int)(start->x /c->tilesize) * c->tilesize + c->tilesize);
		end->y = (end->x - start->x) * ntan + start->y;
		offset.x = c->tilesize;
		offset.y = (offset.x * ntan);	
	}
	int lim_i = c->map_height / c->tilesize;
	int lim_j = c->map_width / c->tilesize;
	while (dof < (lim_j))
	{
		if (end->y >= 0 && end->y < c->map_height && end->x >= 0 && end->x < c->map_width )
		{
			int i = end->y / c->tilesize;
			int j = end->x / c->tilesize;
			if (i < 0 || j <  0  || i > lim_i || j > lim_j || (c->map[i][j] == '1') )
			{
				dof = lim_i;
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
			dof = lim_i;
			break;
		}
	}
}

void draw_one_ray(t_cub *c, double x, double y, float ang, int i)
{
	t_point start;
	t_point	end_vert;
	t_point	end_hor;
	double	vlen;
	double	hlen;

	start.x = x + (0.1 * c->tilesize);
	start.y = y + (0.1 * c->tilesize);
	check_horizontal(c, &start, &end_hor, ang);
	check_vertical(c, &start, &end_vert, ang);
	vlen = sqrt(((end_vert.y - start.y)* (end_vert.y - start.y)) + ((end_vert.x - start.x) * (end_vert.x - start.x)));
	hlen = sqrt(((end_hor.y - start.y)* (end_hor.y - start.y)) + ((end_hor.x - start.x) * (end_hor.x - start.x)));
	if (hlen <= vlen)
	{
		draw_one_line(c, start, end_hor);
		c->rays_len[i] = hlen;
	}
	else 
	{
		draw_one_line(c, start, end_vert);
		c->rays_len[i] = vlen;
	}
}

void draw_rays(t_cub *c, double x, double y)
{
	int i;
	float ang;
	float one_deg;

	i = 0;
	one_deg = 0.0174;
	ang = c->player->ang - (c->view_ang / 2 * one_deg);
	if (c->player->rays)
		mlx_delete_image(c->mlx, c->player->rays);
	c->player->rays = mlx_new_image(c->mlx, c->map_width , c->map_height);
	if (!c->player->rays|| (mlx_image_to_window(c->mlx, c->player->rays,0,0) < 0))
		return ;
	while (i < c->view_ang)
	{
		if (ang >= 2 * PI)
			ang -= 2 * PI;
		else if (ang < 0)
			ang += (2 * PI);
		draw_one_ray(c, x, y, ang, i);
		ang += one_deg;
		i++;
	}
}






