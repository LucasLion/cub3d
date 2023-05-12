/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_graphic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:56:50 by amouly            #+#    #+#             */
/*   Updated: 2023/05/11 13:50:07 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	texture_to_image(t_game *g, int i, int j)
{
	g->texture->height = 64;
	g->texture->width = 64;
	g->img = mlx_texture_to_image(g->mlx, g->texture);
	mlx_image_to_window(g->mlx, g->img, j * 64, i * 64);
	mlx_delete_texture(g->texture);
}

int	load_texture(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	while (g->map[++i])
	{
		j = -1;
		while (g->map[i][++j])
		{
			if (g->map[i][j] == '1')
				g->texture = mlx_load_png("./images/black.png");
			else if (g->map[i][j] == '0')
				g->texture = mlx_load_png("./images/wall.png");
			texture_to_image(g, i, j);
		}
	}
	return (1);
}

/*void	print_char(t_so_long *sl)
{
	char	*ret;
	char	*itoa;

	sl->steps++;
	itoa = ft_itoa(sl->steps);
	ret = ft_strjoin("Nombre de move : ", itoa);
	ft_printf("nombre de move : %d\n", sl->steps);
	mlx_delete_image(sl->mlx, sl->text);
	sl->text = mlx_put_string(sl->mlx, ret, 0, 0);
	free(ret);
	free(itoa);
}*/

void	hook_key(mlx_key_data_t keydata, void *param)
{
	t_game		*g;
	mlx_t		*mlx;

	g = param;
	mlx = g->mlx;
	if ((keydata.key == MLX_KEY_ESCAPE) && keydata.action == 1)
		mlx_close_window(mlx);
	/*if ((keydata.key == MLX_KEY_W) && keydata.action == 1)
		move_up(sl);
	if ((keydata.key == MLX_KEY_S) && keydata.action == 1)
		move_down(sl);
	if ((keydata.key == MLX_KEY_A) && keydata.action == 1)
		move_left(sl);
	if ((keydata.key == MLX_KEY_D) && keydata.action == 1)
		move_right(sl);*/
}

int	add_graphic(t_game *g)
{
	g->mlx = mlx_init(g->map_width * 64, g->map_height * 64, "CUBE3D",
			true);
	if (!(g->mlx))
		exit(EXIT_FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	if (!(load_texture(g)))
		return (0);
	//sl->text = mlx_put_string(sl->mlx, "nombre de move : 0", 0, 0);
	mlx_key_hook(g->mlx, &hook_key, g);
	mlx_loop(g->mlx);
	//mlx_terminate(g->mlx);
	return (1);
}
