/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/16 16:54:33 by amouly           ###   ########.fr       */
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
		mlx_put_pixel(c->player->line, start.x, start.y, 0xff0456ff); 
		start.y += delta_y;
		start.x += delta_x;
		--length;
	}
	
}



void draw_line(t_cub *c, int x, int y)
{
	t_point	start;
	t_point end;
	double	ra;
	double 	atan;
	int 	y_offset;
	double	x_offset;	

	ra = c->player->ang;
	atan = 1 / tan(ra); 
	printf("ang : %f\n", ra);
	if (c->player->line)
		mlx_delete_image(c->mlx, c->player->line);
	c->player->line = mlx_new_image(c->mlx, c->map_width , c->map_height);
	if (!c->player->line|| (mlx_image_to_window(c->mlx, c->player->line,0,0) < 0))
		return ;
	start.x = x + (0.1 * c->tilesize);
	start.y = y + (0.1 * c->tilesize);
	if (ra > PI) 
	{
		end.y = (int)(start.y /c->tilesize) * c->tilesize + c->tilesize;
		end.x = (end.y - start.y) * atan + start.x;
		y_offset = c->tilesize;
		x_offset = (y_offset * atan);	
	}
	if (ra < PI) 
	{
		end.y = ((int)(start.y /c->tilesize) * c->tilesize - 0.001);
		end.x = (end.y - start.y) * atan + start.x;
		y_offset = - (c->tilesize);
		x_offset = -(y_offset * atan);	
	}
	if (ra == 0 || ra == PI) 
	{
		end.y = start.y;
		end.x = start.x;
	}
	int dof = 0;
	while(dof < c->map_height)
	{
		int i = end.y / c->tilesize;
		int j = end.x / c->tilesize;
		printf("i / j  : %d / %d map[i][j] : %c\n", i, j, c->map[i][j] );
		printf("end x / y  : %f / %f\n", end.x, end.y );
		if (c->map[i][j] == '1')
			dof = c->map_height;
		else	
			{
				end.x += x_offset;
				end.y += y_offset;
				dof++;
			}
	}
	//end.x =  (cosf(c->player->ang) * 60) + start.x ;
	//end.y =  (sinf(c->player->ang) * 60) + start.y ;
	
	draw_one_line(c, start, end);	
}

/*void draw_line(t_cub *c, int x, int y)
{
	t_line	line;

	if (c->player->line)
		mlx_delete_image(c->mlx, c->player->line);
	line.len_line = 60;
	line.start_x = x + (0.1 * c->tilesize);
	line.start_y = y + (0.1 * c->tilesize);
	line.end_x =  ((cos(c->player->ang) * line.len_line)) + line.start_x ;
	line.end_y = - ((sin(c->player->ang) * line.len_line)) + line.start_y ;
	line.delta_x = line.end_x - line.start_x;
	line.delta_y = line.end_y - line.start_y;
	c->player->line = mlx_new_image(c->mlx, c->map_width , c->map_height);
	if (!c->player->line|| (mlx_image_to_window(c->mlx, c->player->line,0,0) < 0))
		return ;
	line.delta_x /= line.len_line;
	line.delta_y /= line.len_line;
	while(line.len_line)
	{
		mlx_put_pixel(c->player->line, line.start_x, line.start_y, 0xff0456ff); 
		line.start_y += line.delta_y;
		line.start_x += line.delta_x;
		--line.len_line;
	}
	
}*/




