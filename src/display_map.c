/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/31 12:07:15 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_square(t_cub *c, int x, int y, long int color)
{
	int	i;
	int	j;
	mlx_image_t	*img;

	i = 0;
	img = mlx_new_image(c->mlx, c->tilesize_H_2d, c->tilesize_V_2d);
	
	
	while (i < c->tilesize_H_2d)
	{
		j = 0;
		while (j < c->tilesize_V_2d)
		{
			mlx_put_pixel(img, i, j, color); 
			j++;
		}
		i++;
	}
	if (!img || (mlx_image_to_window(c->mlx, img, 80 + y * c->tilesize_H_2d , 80 + x * c->tilesize_V_2d ))< 0)
		return ;
	img->instances[0].z = 1;
}

int	display_2d_map(t_cub *c)
{
	int			i;
	int 		j;

	i = 0;
	while (c->map[i])
	{
		j = 0;
		while (c->map[i][j])
		{
			if (c->map[i][j] == '0' || c->map[i][j] == 'W' || c->map[i][j] == 'E' \
				|| c->map[i][j] == 'S' || c->map[i][j] == 'N')
			{
				put_square(c, i, j, 0xffffff55);
				if (c->map[i][j] != '0')
				{
					c->player->m_pos.x = i;
					c->player->m_pos.y = j;
				}
			}
			else if (c->map[i][j] == '1')
				put_square(c, i, j, 0x00000055);
			j++;
		}
		i++;
	}
	return (1);
}

void	draw_ceiling(t_cub *c, t_point start, t_point end)
{
	t_point sta_ceil;
	t_point end_ceil;

	sta_ceil.y = 0;
	sta_ceil.x = start.x;
	end_ceil.y = start.y;
	end_ceil.x = start.x;
	draw_one_line(c, c->img3d, sta_ceil, end_ceil, c->t->ceiling);
}

void	draw_floor(t_cub *c, t_point start, t_point end)
{
	t_point sta_floor;
	t_point end_floor;

	sta_floor.y = end.y;
	sta_floor.x = start.x;
	end_floor.y = SCREEN_HEIGHT;
	end_floor.x = start.x;
	draw_one_line(c, c->img3d, sta_floor, end_floor, c->t->floor);
}


int	display_3d_map(t_cub *c)
{
	int					i;
	int					j;
	int					line_height;
	t_point				start;
	t_point				end;
	unsigned long color = 0;
	
	start.x = 0;
	i = c->view_ang - 1;
	if (c->img3d)
		mlx_delete_image(c->mlx, c->img3d);
	c->img3d = mlx_new_image(c->mlx, SCREEN_WIDTH , SCREEN_HEIGHT);
	if (!c->img3d || (mlx_image_to_window(c->mlx, c->img3d, 0, 0) < 0))
		return 0;
	c->img3d->instances[0].z = 0;
	while(i >= 0)
	{
		j = 0;
		while(j <= SCREEN_WIDTH / c->view_ang)
		{
			int pixel = 0;
			line_height = SCREEN_HEIGHT / c->rays[i].len * c->tilesize_V * DEPTH;
			start.y = ((SCREEN_HEIGHT) - line_height) / 2;
			end.x = start.x;
			end.y = line_height + start.y;
			draw_ceiling(c, start, end);
			draw_floor(c, start, end);
			while (start.y < end.y)
			{
				if (((start.x < (c->map_width * c->tilesize_H) - 1) &&  start.x > 0) \
					&& (start.y < ((c->map_height * c->tilesize_V) - 1) && start.y > 0))
					mlx_put_pixel(c->img3d, start.x, start.y, c->rays[i].color );
				start.y++;
			}
			j++;
			start.x++;
		}
		i--;
	}
	return (1);
}
