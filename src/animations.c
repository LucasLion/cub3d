/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:20:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/06 16:37:37 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	**load_animation(t_cub *c)
{
	mlx_texture_t	**t;

	t = ft_calloc(sizeof(mlx_texture_t *), 5);
	t[0] = mlx_load_png("./textures/anim1.png");
	t[1] = mlx_load_png("./textures/anim2.png");
	t[2] = mlx_load_png("./textures/anim3.png");
	t[3] = mlx_load_png("./textures/anim4.png");
	t[4] = mlx_load_png("./textures/anim5.png");
	return (t);
}

void	draw_anim(t_cub *c, int x)
{
}

int	animation(t_cub *c)
{
	static int	x = 0;

	while (x <= 60)
	{
		c->player->img = mlx_texture_to_image(c->mlx, c->player->texture[x]);
		mlx_image_to_window(c->mlx, c->player->img, 100, 100);
		x++;
	}
	x = 0;
	return (1);
}
