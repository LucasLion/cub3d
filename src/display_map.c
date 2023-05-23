/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/23 11:50:59 by amouly           ###   ########.fr       */
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

int	display_3d_map(t_cub *c)
{
	int			i;
	int			j;
	int			line_height;
	t_point		start;
	t_point		end;

	start.y = c->map_height * c->tilesize;
	start.x = 0;
	i = 0;
	j = 0;
	while(i < c->view_ang)
	{
		j = 0;
		while(j < c->map_width / c->view_ang * c->tilesize)
		{
			line_height = c->map_height * c->map_width * c->map_height * c->tilesize / c->rays_len[i];
			if (line_height > c->map_height * c->tilesize)
				line_height = c->map_height * c->tilesize;
			end.x = start.x;
			end.y = start.y + line_height;
			draw_one_line(c->img, start, end);
			j++;
		}
		start.x += c->map_width / c->view_ang * c->tilesize;
		i++;
	}
	return (1);
}

int	display(t_cub *c)
{
	c->mlx = mlx_init(c->map_width, c->map_height * 2, "CUB3D", true);
	if (!c->mlx)
		return (EXIT_FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	display_2d_map(c);
	return (1);
}
