/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:46:22 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 11:16:22 by amouly           ###   ########.fr       */
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
		if (end->y >= 0 && end->y < (c->tilesize *c->map_height) && end->x >= 0 && end->x < (c->tilesize *c->map_width))
		{
			i = end->y / c->tilesize;
			j = end->x / c->tilesize;
			if (i < 0 || j <  0  || i > c->map_height || j > c->map_width\
				|| (c->map[i][j] == '1') || (c->map[i][j] == '2') || (c->map[i][j] == 'P'))
			{
				if (c->map[i][j] == '2')
					c->rays[ang].h_special = 1;
				if (c->map[i][j] == 'P')
					c->rays[ang].h_special = 2;
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
		if (end->y >= 0 && end->y < (c->tilesize *c->map_height) && end->x >= 0 && end->x < (c->tilesize *c->map_width))
		{
			i = end->y / c->tilesize;
			j = end->x / c->tilesize;
			if (i < 0 || j <  0  || i > c->map_height || j > c->map_width \
				|| (c->map[i][j] == '1') || (c->map[i][j] == '2') || (c->map[i][j] == 'P'))
			{
				if (c->map[i][j] == '2')
					c->rays[ang].v_special = 1;
				if (c->map[i][j] == 'P')
					c->rays[ang].v_special = 2;
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
	loop_v(c, offset, ray, end);
}

t_point	reduce_point(t_point p, t_cub *c)
{
	p.x =  ((p.x) / c->tilesize * c->tilesize_2d);
	p.y =  ((p.y) /  c->tilesize * c->tilesize_2d);
	return (p);
}

