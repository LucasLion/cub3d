/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:46:22 by llion             #+#    #+#             */
/*   Updated: 2023/06/04 11:48:56 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	loop_h(t_cub *c, t_point offset, int dof, t_point *end)
{
	while (dof < c->map_height)
	{
		if (end->y >= 0 && end->y < (c->true_screen_height) && end->x >= 0 && end->x < (c->true_screen_width) )
		{
			int i = end->y / c->tilesize_V;
			int j = end->x / c->tilesize_H;
			if (i < 0 || j <  0  || i > c->map_height || j > c->map_width || (c->map[i][j] == '1') || (c->map[i][j] == '2'))
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

void check_horizontal(t_cub *c, t_point *start, t_point *end, float ang)
{
	t_point offset;
	int		i;
	float	ra = ang;
	float	atan = -1 / tan(ra);
	
	i = 0;
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
	loop_h(c, offset, i, end);
}

void	loop_v(t_cub *c, t_point offset, int dof, t_point *end)
{
	while (dof < (c->map_width))
	{
		if (end->y >= 0 && end->y < (c->true_screen_height) && end->x >= 0 && end->x < (c->true_screen_width))
		{
			int i = end->y / c->tilesize_V;
			int j = end->x / c->tilesize_H;
			if (i < 0 || j <  0  || i > c->map_height || j > c->map_width || (c->map[i][j] == '1') || (c->map[i][j] == '2'))
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
	loop_v(c, offset, dof, end);
}

t_point	reduce_point(t_point p, t_cub *c)
{
	p.x =  (p.x) / c->tilesize_H * c->tilesize_H_2d;
	p.y =  (p.y) /  c->tilesize_V * c->tilesize_V_2d;
	return (p);
}

