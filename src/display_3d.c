/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 14:45:22 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	pix_draw(t_cub *c, mlx_texture_t *texture, int start_y)
{
	int	pixel;

	pixel = 0;
	while (pixel < c->line_h)
	{
		if (((c->start.x < (c->true_screen_width) - 1) && c->start.x >= -10)
			&& (start_y + pixel < ((SCREEN_HEIGHT) - 1) \
			&& start_y + pixel >= 0))
		{
			c->color_pix = get_color_pixel(texture, c->pix.x, c->pix.y);
			mlx_put_pixel(c->img3d, c->start.x, start_y + pixel, c->color_pix);
		}
		pixel++;
		c->pix.y += c->ty_step;
	}
}

void	draw_pixels(t_cub *c, mlx_texture_t *texture)
{
	int	pixel;

	pixel = 0;
	if (c->line_h < SCREEN_HEIGHT)
		pix_draw(c, texture, c->start.y);
	else
	{
		c->pix.y = -(c->start.y * c->ty_step);
		c->line_h = SCREEN_HEIGHT;
		pix_draw(c, texture, 0);
	}
}

void	init_display_3d(t_cub *c)
{
	c->start.x = 0;
	c->pix.x = 0;
	if (c->img3d)
		mlx_delete_image(c->mlx, c->img3d);
	c->img3d = mlx_new_image(c->mlx, c->true_screen_width, SCREEN_HEIGHT);
	if (!c->img3d || (mlx_image_to_window(c->mlx, c->img3d, 0, 0) < 0))
		return ;
	c->img3d->instances[0].z = 1;
}

int	display_3d_map(t_cub *c)
{
	int				i;
	int				j;
	mlx_texture_t	*texture;

	i = c->view_ang - 1;
	init_display_3d(c);
	while (i >= 0)
	{
		j = 0;
		while (j < c->true_screen_width / c->view_ang)
		{
			c->pix.y = 0;
			calculate_pix_x(c, i, &texture);
			c->line_h = SCREEN_HEIGHT / c->rays[i].len * c->tilesize * DEPTH;
			c->ty_step = texture->height / (float)c->line_h;
			c->start.y = ((SCREEN_HEIGHT) - c->line_h) / 2;
			c->end.x = c->start.x;
			c->end.y = c->line_h + c->start.y;
			draw_pixels(c, texture);
			j++;
			c->start.x++;
		}
		i--;
	}
	return (1);
}
