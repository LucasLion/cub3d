/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/15 16:59:03 by amouly           ###   ########.fr       */
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

void	put_player_square(t_cub *c, int x, int y)
{
	c->player->img = mlx_new_image(c->mlx, c->tilesize, c->tilesize);
	if (!c->player->img || (mlx_image_to_window(c->mlx, c->player->img, (y + 0.4) * c->tilesize, (x + 0.4) * c->tilesize) < 0))
		return ;
	int i;
	int	j;

	i = 0;
	while (i < (c->tilesize * 0.2))
	{
		j = 0;
		while (j < (c->tilesize * 0.2))
		{
			mlx_put_pixel(c->player->img, i, j, 0xff0456ff); 
			j++;
		}
		i++;
	}
}

int	display_2d_map(t_cub *c)
{
	int			i;
	int 		j;

	c->mlx = mlx_init(c->map_width, c->map_height, "CUB3D", true);
	if (!c->mlx)
		return (EXIT_FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
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
