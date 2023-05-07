/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/05/07 17:42:39 by llion            ###   ########.fr       */
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

	file = get_file();
	if (parsing(file) == 0)
	{
		ft_freetab(file);
		ft_error("Error: Invalid map\n");
		return (-1);
	}
	ft_freetab(file);
	return (0);
}
