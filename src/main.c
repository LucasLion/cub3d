/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/05/11 16:07:57 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

int	free_function(char **file, t_textures *t)
{
	ft_freetab(file);
	ft_freetab(t->map);
	free(t);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**file;
	t_textures	*t;

	t = ft_calloc(1, sizeof(t_textures));
	file = get_file();
	if (parsing(file, t) == 0 || parse_file(argc, argv) == 0)
	{
		free_function(file, t);
		ft_error("Error: Invalid map");
		return (-1);
	}
	free_function(file, t);
	return (0);
}
