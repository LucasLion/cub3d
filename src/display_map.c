/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/23 13:37:29 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_square(t_cub *c, int x, int y, long int color)
{
	int	i;
	int	j;
	mlx_image_t	*img;

	i = 0;
	img = mlx_new_image(c->mlx, c->tilesize, c->tilesize);
	if (!img || (mlx_image_to_window(c->mlx, img, y * c->tilesize, x * c->tilesize) < 0))
		return ;
	while (i < c->tilesize - 1)
	{
		j = 0;
		while (j < c->tilesize - 1)
		{
			mlx_put_pixel(img, i, j, color); 
			j++;
		}
		i++;
	}
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
				put_square(c, i, j, 0xffffffff);
				if (c->map[i][j] != '0')
					c->player = init_player(c, i, j);
			}
			else if (c->map[i][j] == '1')
				put_square(c, i, j, 0x000000ff);
			j++;
		}
		i++;
	}
	return (1);
}

void	line_offset(t_cub *c)
{
}

int	display_3d_map(t_cub *c)
{
	int			i;
	int			j;
	int			line_height;
	t_point		start;
	t_point		end;
	long unsigned int	color;

	start.x = 0;
	i = c->view_ang - 1;
	color = 0xff0000ff;
	while(i >= 0)
	{
		j = 0;
		while(j < c->screen_width / c->view_ang)
		{
			line_height = c->map_width / c->rays_len[i] * c->screen_height;
			start.y = c->screen_height - (line_height / 2) + (c->screen_height / 2);
			if (line_height > c->screen_height)
				line_height = c->screen_height;
			end.x = start.x;
			end.y = start.y + line_height;
			draw_one_line(c->img, start, end, color + (line_height / 2));
			printf("endy: %f\n", end.y);
			j++;
			start.x++;
		}
		i--;
	}
	return (1);
}

int	display(t_cub *c)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	display_2d_map(c);
	return (1);
}
