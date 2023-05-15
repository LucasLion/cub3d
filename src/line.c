/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/15 16:57:58 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	wall_or_empty(t_cub *c, int x , int y)
{
	int j = x / c->tilesize;
	int i = y / c->tilesize;
	printf("x : %d et y : %d\n", x, y);
	printf("i : %d et j : %d\n", i, j);
	printf("le carcterre [1][3] : %c \n",  c->map[1][3] );
	printf("le carcterre [3][1] : %c \n",  c->map[3][1] );
	printf("le carcterre de la map %c \n", c->map[i][j] );
	
	c->test = 1;
	return (0);
}

void draw_line(t_cub *c, int x, int y)
{
	t_line	line;

	if (c->player->line)
		mlx_delete_image(c->mlx, c->player->line);
	line.len_line = 60;
	if (c->test == 0)
	{
		printf ("debut de draw x==>%d et y ==> %d\n", x ,y);
		printf ("coordonee j ==> %d et i ==> %d\n", x / c->tilesize , y / c->tilesize );
	}
	line.start_x = x + (0.1 * c->tilesize);
	line.start_y = y + (0.1 * c->tilesize);
	line.end_x =  ((cos(c->player->ang) * line.len_line)) + line.start_x ;
	line.end_y = - ((sin(c->player->ang) * line.len_line)) + line.start_y ;
	line.delta_x = line.end_x - line.start_x;
	line.delta_y = line.end_y - line.start_y;
	if (c->test == 0)
		wall_or_empty(c ,line.end_x, line.end_y );
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

