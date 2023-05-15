/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/15 15:17:25 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_player(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

	c = param;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		c->player->is_moving = 2;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		c->player->is_moving = 4;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
}

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
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		c->player->is_moving = 5;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		c->player->is_moving = 6;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		c->player->is_moving = 0;
}

void	check_movement(t_cub *c)
{
	if (c->player->is_moving == 1)
	{
		c->player->img->instances[0].y -= 1;
		c->player->line->instances[0].y -= 1;
	}
	else if (c->player->is_moving == 2)
	{
		c->player->img->instances[0].x -= 1;
		c->player->line->instances[0].x -= 1;
	}
	else if (c->player->is_moving == 3)
	{
		c->player->img->instances[0].y += 1;
		c->player->line->instances[0].y += 1;
	}
	else if (c->player->is_moving == 4)
	{
		c->player->img->instances[0].x += 1;
		c->player->line->instances[0].x += 1;
	}
	if (c->player->is_moving == 5)
	{
		c->player->ang -= 0.1;
		if (c->player->ang < 0)
			c->player->ang += (2 * PI);
	}
	else if (c->player->is_moving == 6)
	{
		c->player->ang += 0.1;
		if (c->player->ang > (2 * PI))
			c->player->ang -= (2 * PI);
	}
}

void	ft_hook(void *param)
{
	t_cub *c;

	c = param;
	check_movement(c);
	draw_line(c, c->player->img->instances[0].x, c->player->img->instances[0].y);
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

void	put_player_L(t_cub *c, int x, int y)
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
int	wall_or_empty(t_cub *c, double x , double y)
{
	int i = x / c->tilesize;
	int j = y / c->tilesize;
	printf("x : %f et y : %f", x, y);
	printf("i : %d et j : %d", i, j);
	c->test = 1;
	return (0);
}

void draw_line(t_cub *c, int x, int y)
{
	t_line	line;

	if (c->player->line)
		mlx_delete_image(c->mlx, c->player->line);
	line.len_line = 60;
	line.start_x = y;
	line.start_y = x;
	line.end_x =  (cos(c->player->ang) * line.len_line) + y ;
	line.end_y = - ((sin(c->player->ang) * line.len_line)) + x ;
	line.delta_x = line.end_x - line.start_x;
	line.delta_y = line.end_y - line.start_y;
	if (c->test == 0)
		wall_or_empty(c ,line.end_x, line.end_y );
	c->player->line = mlx_new_image(c->mlx, c->map_width , c->map_height);
	if (!c->player->line|| (mlx_image_to_window(c->mlx, c->player->line,c->tilesize * 0.1, c->tilesize * 0.1) < 0))
		return ;
	line.delta_x /= line.len_line;
	line.delta_y /= line.len_line;
	while(line.len_line)
	{
		mlx_put_pixel(c->player->line, line.start_y, line.start_x, 0xff0456ff); 
		line.start_y += line.delta_x;
		line.start_x += line.delta_y;
		--line.len_line;
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
