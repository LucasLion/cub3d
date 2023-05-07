/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:31:32 by llion             #+#    #+#             */
/*   Updated: 2023/05/07 18:55:33 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"


int	parse_description(char **description)
{
	// TODO 
	(void)description;
	return (1);
}


int	parse_elems(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N' \
					&& map[i][j] != 'S' && map[i][j] != 'E' \
					&& map[i][j] != 'W' && map[i][j] != ' ' && map[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_borders(char **map)
{
	(void)map;
	// TODO
	// Check if the map is surrounded by walls
	// Find a way to check if the last line in the example is valid
	return (1);
}

int	parsing(char **file)
{
	char	**description;
	char	**map;

	description = get_description(file);
	map = get_map(file);
	// TODO
	// Check if there is only one player
	if (parse_description(description) == 0 || parse_elems(map) == 0 \
			|| parse_borders(map) == 0)
	{
		ft_freetab(description);
		ft_freetab(map);
		return (0);
	}
	ft_freetab(description);
	ft_freetab(map);
	return (1);
}
