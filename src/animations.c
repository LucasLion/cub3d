/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:20:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 14:21:39 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	**load_texture_anim(t_cub *c)
{
	mlx_texture_t	**t;

	t = ft_calloc(sizeof(mlx_texture_t *), 15);
	t[0] = mlx_load_png("./textures/1.png");
	t[1] = mlx_load_png("./textures/2.png");
	t[2] = mlx_load_png("./textures/3.png");
	t[3] = mlx_load_png("./textures/4.png");
	t[4] = mlx_load_png("./textures/5.png");
	t[5] = mlx_load_png("./textures/6.png");
	t[6] = mlx_load_png("./textures/7.png");
	t[7] = mlx_load_png("./textures/8.png");
	t[8] = mlx_load_png("./textures/9.png");
	t[9] = mlx_load_png("./textures/10.png");
	t[10] = mlx_load_png("./textures/11.png");
	t[11] = mlx_load_png("./textures/12.png");
	t[12] = mlx_load_png("./textures/13.png");
	t[13] = mlx_load_png("./textures/14.png");
	t[14] = mlx_load_png("./textures/15.png");
	return (t);
}

int	animation(t_cub *c)
{
	static int	x = 0;

	c->static_var = x;
	if (x >= 14)
		x = 0;
	x++;
	return (1);
}
