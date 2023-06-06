/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:20:09 by llion             #+#    #+#             */
/*   Updated: 2023/06/06 14:48:38 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_image_t	**load_animation(t_cub *c)
{
	mlx_texture_t	*t[5];
	mlx_image_t		**img;
	int				i;

	i = 0;
	img = ft_calloc(sizeof(mlx_image_t), 5);
	t[0] = mlx_load_png("./textures/anim1.png");
	t[1] = mlx_load_png("./textures/anim2.png");
	t[2] = mlx_load_png("./textures/anim3.png");
	t[3] = mlx_load_png("./textures/anim4.png");
	t[4] = mlx_load_png("./textures/anim5.png");
	while (i < 5)
	{
		img[i] = mlx_texture_to_image(c->mlx, t[i]);
		i++;
	}
	return (img);
}

void	draw_anim(t_cub *c, int x)
{
	mlx_image_t	**img;

	img = load_animation(c);
	if (x == 0)
		mlx_delete_image(c->mlx, img[4]);
	else if (x == 1)
		mlx_delete_image(c->mlx, img[0]);
	else if (x == 2)
		mlx_delete_image(c->mlx, img[1]);
	else if (x == 3)
		mlx_delete_image(c->mlx, img[2]);
	else if (x == 4)
		mlx_delete_image(c->mlx, img[3]);
	printf("x: %d\n", x);
	mlx_image_to_window(c->mlx, img[x], c->true_screen_width - 4 * img[x]->width, c->true_screen_height - img[x]->height);
}

int	animation(t_cub *c)
{
	static float	x = 0;

	while (x <= 4)
	{
		draw_anim(c, x);
		x += 0.2;
	}
	draw_anim(c, 0);
	return (1);
}
