/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/12 15:38:17 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

	c = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(c->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		c->player->y_start -= 1;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		c->player->y_start += 1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		c->player->x_start -= 1;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		c->player->x_start += 1;
}

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

void	put_player(t_cub *c, int x, int y)
{
	mlx_image_t	*img;

	img = mlx_new_image(c->mlx, c->tilesize, c->tilesize);
	if (!img || (mlx_image_to_window(c->mlx, img, y * c->tilesize + (0.5 * c->tilesize) - 4, x*c->tilesize + (0.5 * c->tilesize) - 4) < 0))
		return ;
	int i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			mlx_put_pixel(img, i, j, 0xff0000ff); 
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
				put_square(c, i, j, 0xffffffff);
			else if (c->map[i][j] == '1')
				put_square(c, i, j, 0x000000ff);
			if (c->map[i][j] == 'W' || c->map[i][j] == 'E' \
				|| c->map[i][j] == 'S' || c->map[i][j] == 'N')
			{
				c->player = init_player(c, i, j);
				put_player(c, i, j);
			}
			j++;
		}
		i++;
	}
	return (1);

}
