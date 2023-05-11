/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/05/11 18:00:21 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	display_2d_map(t_cub *c)
{
	mlx_image_t	*img;

	c->mlx = mlx_init(800, 600, "CUB3D", true);
	if (!c->mlx)
		return (EXIT_FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	img = mlx_new_image(c->mlx, 256, 256);
	if (!img || (mlx_image_to_window(c->mlx, img, 0, 0) < 0))
		return (EXIT_FAILURE);

	// TODO affichage de la map 3d
	
	//int	i = 0;
	//int j;
	//while (c->map[i])
	//{
	//	j = 0;
	//	while (c->map[i][j])
	//	{
	//		if (c->map[i][j] == '1')
	//		j++;
	//	}
	//	j++;
	//}
	
	mlx_put_pixel(img, 10, 10, 0xFF0000FF);
	mlx_loop(c->mlx);	
	return (1);

}
