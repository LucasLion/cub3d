/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/05 13:04:01 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void calculate_pix_x(t_cub *c, int i, mlx_texture_t **t)
{
	if (c->rays[i].dir == 'N' || c->rays[i].dir == 'S')
	{
		*t = c->textures[0];
		c->pix.x =  (int)(c->rays[i].wall.x) % c->tilesize_H;
		if (c->rays[i].ang > PI)
		{
			*t = c->textures[1];
			c->pix.x = (c->tilesize_H - c->pix.x - 1) * (*t)->width / c->tilesize_H;
		}
		else
			c->pix.x = c->pix.x * (*t)->width / c->tilesize_H ;
	}
	else
	{
		*t = c->textures[2];
		c->pix.x =  (int)(c->rays[i].wall.y) % c->tilesize_V;
		if (c->rays[i].ang > PI / 2 && c->rays[i].ang < PI / 2 * 3)
		{
			*t = c->textures[3];
			c->pix.x = (c->tilesize_V - c->pix.x - 1) * (*t)->width / c->tilesize_V;
		}
		else
			c->pix.x = c->pix.x * (*t)->width / c->tilesize_V ;
	}
}


void pix_draw(t_cub *c, mlx_texture_t *texture, int start_y)
{
	int pixel;

	pixel = 0;
	while (pixel < c->line_H )
	{ 
		if (((c->start.x < (c->true_screen_width) - 1) &&  c->start.x > 0) \
			&& (start_y + pixel < ((c->true_screen_height) - 1) && start_y + pixel > 0))
			{
				c->color_pix = get_color_pixel(texture, c->pix.x, c->pix.y);
				mlx_put_pixel(c->img3d, c->start.x, start_y + pixel, c->color_pix);
			}
			pixel++;
			c->pix.y += c->ty_step;
	}
}

void draw_pixels(t_cub *c, mlx_texture_t *texture)
{
	int pixel;

	pixel = 0;
	if (c->line_H < c->true_screen_height)
		pix_draw(c, texture, c->start.y);
	else
	{
		c->pix.y = - (c->start.y * c->ty_step);
		c->line_H = c->true_screen_height; 
		pix_draw(c, texture, 0);
	}
}

void init_display_3d(t_cub *c, int i)
{
	c->start.x = 0;
	c->pix.x = 0;
	i = c->view_ang - 1;
	if (c->img3d)
		mlx_delete_image(c->mlx, c->img3d);
	c->img3d = mlx_new_image(c->mlx, c->true_screen_width, c->true_screen_height);
	if (!c->img3d || (mlx_image_to_window(c->mlx, c->img3d, 0, 0) < 0))
		return ;
	c->img3d->instances[0].z = 1;
}

int	display_3d_map(t_cub *c)
{
	int					i;
	int					j;
	mlx_texture_t		*texture;
	
	init_display_3d(c, i);
	while(i >= 0)
	{
		j = 0;
		while(j <= c->true_screen_width/ c->view_ang)
		{
			c->pix.y = 0;
			calculate_pix_x(c, i, &texture);
			c->line_H = c->true_screen_height / c->rays[i].len * c->tilesize_V * DEPTH;
			c->ty_step = texture->height / (float)c->line_H;
			c->start.y = ((c->true_screen_height) - c->line_H) / 2;
			c->end.x = c->start.x;
			c->end.y = c->line_H + c->start.y;
			draw_pixels(c, texture);
			j++;
			c->start.x++;
		}
		i--;
	}
	return (1);
}

