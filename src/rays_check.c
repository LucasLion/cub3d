/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:46:22 by llion             #+#    #+#             */
/*   Updated: 2023/06/05 16:35:20 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	loop_h(t_cub *c, t_point offset, int ang, t_point *end)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (k < c->map_height)
	{
		if (end->y >= 0 && end->y < (c->true_screen_height) && end->x >= 0 && end->x < (c->true_screen_width) )
		{
			i = end->y / c->tilesize_V;
			j = end->x / c->tilesize_H;
			if (i < 0 || j <  0  || i > c->map_height || j > c->map_width || (c->map[i][j] == '1') || (c->map[i][j] == '2'))
			{
				if (c->map[i][j] == '2')
					c->rays[ang].h_door = 1;
				k = c->map_height;
				break;
			}
			else	
			{
				end->x += offset.x;
				end->y += offset.y;
				k++;
			}
		}
		else	
		{
			k = c->map_height;
			break;
		}
	}
}

void check_horizontal(t_cub *c, t_point *start, t_point *end, int ray)
{
	t_point offset;
	float	ra;
	float	atan;
	
	ra = c->rays[ray].ang;
	atan = -1 / tan(ra);
	
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
	loop_h(c, offset, ray, end);
}

void	loop_v(t_cub *c, t_point offset, int ang, t_point *end)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (k < (c->map_width))
	{
		if (end->y >= 0 && end->y < (c->true_screen_height) && end->x >= 0 && end->x < (c->true_screen_width))
		{
			i = end->y / c->tilesize_V;
			j = end->x / c->tilesize_H;
			if (i < 0 || j <  0  || i > c->map_height || j > c->map_width || (c->map[i][j] == '1') || (c->map[i][j] == '2'))
			{
				if (c->map[i][j] == '2')
					c->rays[ang].v_door = 1;
				k = c->map_width;
				break;
			}
			else	
			{
				end->x += offset.x;
				end->y += offset.y;
				k++;
			}
		}
		else	
		{
			k = c->map_width;
			break;
		}
	}
}

void check_vertical(t_cub *c, t_point *start, t_point *end, int ray)
{
	t_point offset;
	float	ra;
	float	ntan;

	ra = c->rays[ray].ang;
	ntan = -tan(ra);
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
	loop_v(c, offset, ray, end);
}

t_point	reduce_point(t_point p, t_cub *c)
{
	p.x =  (p.x) / c->tilesize_H * c->tilesize_H_2d;
	p.y =  (p.y) /  c->tilesize_V * c->tilesize_V_2d;
	return (p);
}

