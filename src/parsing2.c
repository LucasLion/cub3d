/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:43:14 by llion             #+#    #+#             */
/*   Updated: 2023/05/16 14:41:15 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_file(int argc, char **av)
{
	int		i;

	i = 0;
	if (argc < 2)
		return (ft_error("The program needs map PATH as parameter"));
	else if (argc == 2)
	{
		while (av[1][i])
			i++;
		if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' || av[1][i - 3] != 'c' \
				|| av[1][i - 4] != '.')
			return (ft_error("Wrong extension or file"));
		return (1);
	}
	else
		return (0);
}
