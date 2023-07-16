/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:31:32 by llion             #+#    #+#             */
/*   Updated: 2023/07/16 15:53:30 by llion@student    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_elems_in_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != '\0' && map[i][j] != 'W' && map[i][j] != ' '
				&& map[i][j] != '\n' && map[i][j] != 'P')
				return (ft_error("Invalid map (foreign chars)"));
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_borders(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (map[i][j] == '\n')
			i++;
		while (map[i][j])
		{
			if (i == 0 || i == ft_tablen(map) - 1 || j == 0
				|| j == (int)ft_strlen(map[i]) - 2)
			{
				if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\n')
					return (ft_error("Map needs to be closed"));
			}
			else if (check_spaces(map[i][j], map, i, j) == 0)
				return (ft_error("Map needs to be closed"));
			j++;
		}
		i++;
	}
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
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				nb_players++;
			j++;
		}
		i++;
		if (i > 50 || j > 50)
			return (ft_error("Map too big"));
	}
	if (nb_players != 1)
		return (ft_error("Wrong number of players"));
	return (1);
}

int	parsing(char **file, t_cub *c)
{
	if (parse_infos(file, c) == 0 || parse_elems_in_map(c->map) == 0
		|| parse_borders(c->map) == 0 || parse_number_players(c->map) == 0)
		return (0);
	return (1);
}
