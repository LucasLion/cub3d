/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/12 18:37:51 by amouly           ###   ########.fr       */
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
		c->player->is_moving = 1;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		c->player->is_moving = 2;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		c->player->is_moving = 3;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		c->player->is_moving = 4;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
}

void	check_movement(t_cub *c)
{
	if (c->player->is_moving == 1)
		c->player->img->instances[0].y -= 1;
	else if (c->player->is_moving == 2)
		c->player->img->instances[0].x -= 1;
	else if (c->player->is_moving == 3)
		c->player->img->instances[0].y += 1;
	else if (c->player->is_moving == 4)
		c->player->img->instances[0].x += 1;
}

void	ft_hook(void *param)
{
	t_cub *c;

	c = param;
	check_movement(c);
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
	c->player->img = mlx_new_image(c->mlx, c->tilesize, c->tilesize);
	if (!c->player->img || (mlx_image_to_window(c->mlx, c->player->img, y * c->tilesize + (0.5 * c->tilesize) - (c->tilesize * 0.1), x*c->tilesize + (0.5 * c->tilesize) - (c->tilesize * 0.2)) < 0))
		return ;
	int i;
	int	j;

	i = 0;
	while (i < (c->tilesize * 0.4))
	{
		j = 0;
		while (j < (c->tilesize * 0.4))
		{
			if (i == 0 )
				mlx_put_pixel(c->player->img, i, j, 0xff0456ff);
			if (j == (c->tilesize * 0.2))
				mlx_put_pixel(c->player->img, i, j, 0xff0456ff);
			j++;
		}
		i++;
	}
}

void	put_arrow(t_cub *c, int x, int y)
{
	c->player->img = mlx_new_image(c->mlx, c->tilesize, c->tilesize);
	if (!c->player->img || (mlx_image_to_window(c->mlx, c->player->img, y * c->tilesize + (0.5 * c->tilesize) - (c->tilesize * 0.1), x*c->tilesize + (0.5 * c->tilesize) - (c->tilesize * 0.1)) < 0))
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
	mlx_put_pixel(c->player->img, 0, 0, 0xf00fffff); 
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
			j++;
		}
		i++;
	}
	i = 0;
	while (c->map[i])
	{
		j = 0;
		while (c->map[i][j])
		{
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
