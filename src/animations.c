/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:20:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 09:32:14 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	*load_texture_anim(t_cub *c, int x)
{
	mlx_texture_t	**t;

	t = ft_calloc(sizeof(mlx_texture_t *), 5);
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
	return (t[x]);
}

mlx_image_t	*load_image(t_cub *c, int x)
{
	int				i;

	i = 0;
	c->t_door = load_texture_anim(c, x);
	while (i < 15)
	{
		c->i_door = mlx_texture_to_image(c->mlx, c->t_door);
		mlx_delete_texture(c->t_door);
		i++;
	}
	return (c->i_door);
}

int	animation(t_cub *c)
{
	static int	x = 0;
	if (x > 60)
		x = 0;
	if (x == 6)
		c->textures[4] = load_texture_anim(c, x);
	return (1);
}
