/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 13:01:57 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned long	get_color_pixel(mlx_texture_t *texture, int x_texture,
		int y_texture)
{
	int	r;
	int	g;
	int	b;
	int	a;
	int	pixel;

	pixel = 4 * x_texture + (y_texture * texture->width * 4);
	r = texture->pixels[pixel];
	g = texture->pixels[pixel + 1];
	b = texture->pixels[pixel + 2];
	a = texture->pixels[pixel + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}
