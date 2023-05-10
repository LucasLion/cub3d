/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/05/10 15:50:49 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

int	main(void)
{
	char	**file;
	t_textures	*t;

	t = ft_calloc(1, sizeof(t_textures));
	file = get_file();
	if (parsing(file, t) == 0)
	{
		ft_freetab(file);
		free(t);
		ft_error("Error: Invalid map");
		return (-1);
	}
	ft_freetab(file);
	free(t);
	return (0);
}
