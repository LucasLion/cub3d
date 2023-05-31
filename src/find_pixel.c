/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/31 11:58:19 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned long get_color_pixel(mlx_texture_t *texture, int x_texture, int y_texture)
{
	int r;
	int g;
	int b;
	int a;
	int pixel;

	pixel = 4 * x_texture + (y_texture * texture->width * 4);
	r = texture->pixels[pixel];
	g = texture->pixels[pixel + 1];
	b = texture->pixels[pixel + 2];
	a = texture->pixels[pixel + 3];
	return (r << 24 | g << 16 | b << 8 | a );

}



unsigned long int get_color_v2(mlx_texture_t *t, int pixel )
{
	int r = t->pixels[pixel];
	int g = t->pixels[pixel +1];
	int b = t->pixels[pixel +2];
	int a = t->pixels[pixel +3];
	return (r << 24 | g << 16 | b << 8 | a );
}



unsigned long int get_pixel_north(t_cub *c, int i, int l_h, int p)
{
    int pos;
    float x;
    float y;
    
    x = ((float)c->textures[0]->height / l_h * p);
    y = ((float)c->textures[0]->width / c->tilesize_V * ((int)c->rays[i].wall.y % c->tilesize_V));
    pos =  ((int) x * c->textures[0]->width + (int) y );
    return (pos);
}

unsigned long int find_color_pixel(t_cub *c, int i, int l_h, int p)
{
    int pixel;
    
    if (c->rays->dir == 'N')
    {
        pixel = get_pixel_north(c, i, l_h, p);
       //return (get_color_v2 (c->textures[0], pixel ));
        return (c->rays[i].color);
    }
    if (c->rays->dir == 'E')
    {
        //pixel = get_pixel_north(c, i, l_h, p);
        return (c->rays[i].color);
    }
    if (c->rays->dir == 'S')
    {
       // pixel = get_pixel_north(c, i, l_h, p);
        return (c->rays[i].color);
    }
    if (c->rays->dir == 'W')
    {
        //pixel = get_pixel_north(c, i, l_h, p);
        return (c->rays[i].color);
    }
    return (0);
} 