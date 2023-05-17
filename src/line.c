/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/17 13:08:28 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_xcross(t_cub *c, t_line *line)
{
	int	opp;

	if (c->player->ang >= 0 && c->player->ang < PI)
	{
		opp = tan(c->player->ang) * c->player->img->instances[0].y + (c->tilesize/10) % c->tilesize;
		line->end_x = c->player->img->instances[0].x - opp + c->tilesize*0.2;
		line->end_y = c->player->img->instances[0].y / c->tilesize * c->tilesize;
	}
	else
	{
		opp = tan(c->player->ang) * c->player->img->instances[0].y - (c->tilesize/10) % c->tilesize;
		line->end_x = -c->player->img->instances[0].x - opp + c->tilesize*0.2;
		line->end_y = c->player->img->instances[0].y / c->tilesize * c->tilesize;
	}
	//else if (c->player->ang >= PI && c->player->ang < (PI/2)*3) 
	//{
	//	opp = tan(c->player->ang) * ((int)(c->player->img->instances[0].y + 0.1 * c->tilesize) % c->tilesize);
	//	line->end_x = -(c->player->img->instances[0].x - opp);
	//	line->end_y = c->player->img->instances[0].y / c->tilesize * c->tilesize;
	//	line->end_y = 250;
	//}
	//else
	//{
	//	opp = tan(c->player->ang) * ((int)(c->player->img->instances[0].y + 0.1 * c->tilesize) % c->tilesize);
	//	line->end_x =-( c->player->img->instances[0].x - opp);
	//	line->end_y = c->player->img->instances[0].y / c->tilesize * c->tilesize;
	//	line->end_y = 250;
	//}

}

void	get_ycross(t_cub *c, t_line *line)
{
	int	opp;

	if (c->player->ang >= 0 && c->player->ang < PI) 
	{
		opp = tan(c->player->ang) * ((int)(c->player->img->instances[0].y + 0.1 * c->tilesize) % c->tilesize);
		line->end_x = c->player->img->instances[0].x - opp;
		line->end_y = c->player->img->instances[0].y / c->tilesize * c->tilesize;
	}
	else
	{
		opp = tan(c->player->ang) * ((int)(c->player->img->instances[0].y + 0.1 * c->tilesize) % c->tilesize);
		line->end_x = c->player->img->instances[0].x - opp;
		line->end_y = c->player->img->instances[0].y / c->tilesize * c->tilesize;
	}
}

void draw_line(t_cub *c, int x, int y)
{
	t_line	line;
	(void)x;
	(void)y;


	get_xcross(c, &line);
	if (c->player->line)
		mlx_delete_image(c->mlx, c->player->line);
	line.len_line = 60;
	line.start_x = x + (c->tilesize/10);
	line.start_y = y + (c->tilesize/10);
	//line.end_x =  ((cos(c->player->ang) * line.len_line)) + line.start_x ;
	//line.end_y = - ((sin(c->player->ang) * line.len_line)) + line.start_y ;
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
}
