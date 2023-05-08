/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/05/08 17:07:45 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	ft_error(char *error)
{
	size_t	i;

	i = 0;
	write(2, "Error: ", 7);
	while (i < ft_strlen(error))
	{
		write(2, error++, 1);
	}
	write(2, "\n", 1);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**file;

	file = get_file(argc, argv);
	if (file == NULL)
		return (-1);
	if (parsing(file) == 0)
	{
		ft_freetab(file);
		return (-1);
	}
	ft_freetab(file);
	return (0);
}
