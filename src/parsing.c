/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:31:32 by llion             #+#    #+#             */
/*   Updated: 2023/05/08 01:00:26 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"


int	parse_infos(char **d)
{
	int		i;
	int		j;

	i = 0;
	while (i < ft_tablen(d))
	{
		j = 0;
		while (d[i][j] == ' ')
			j++;
		if (!((d[i][j] == 'N' && d[i][j + 1] == 'O') || (d[i][j] == 'S' \
				&& d[i][j + 1] == 'O') || (d[i][j] == 'W' \
				&& d[i][j + 1] == 'E') || (d[i][j] == 'E' \
				&& d[i][j + 1] == 'A') || (d[i][j] == 'S' \
				&& d[i][j + 1] == ' ') || (d[i][j] == 'F' \
				&& d[i][j + 1] == ' ') || (d[i][j] == 'C' \
				&& d[i][j + 1] == ' ')))
			return (0);
		i++;
	}
	// TODO
	// parse second part of the description
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

int	parse_number_players(char **map)
{
	int	i;
	int	j;
	int	nb_players;

	i = 0;
	nb_players = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
					|| map[i][j] == 'W')
				nb_players++;
			j++;
		}
		i++;
	}
	if (nb_players != 1)
		return (0);
	return (1);
}

int	parsing(char **file)
{
	char	**description;
	char	**map;

	description = get_description(file);
	map = get_map(file);
	if (parse_description(description) == 0 || parse_elems(map) == 0 \
			|| parse_borders(map) == 0 || parse_number_players(map) != 1)
	{
		ft_freetab(description);
		ft_freetab(map);
		return (0);
	}
	ft_freetab(description);
	ft_freetab(map);
	return (1);
}
