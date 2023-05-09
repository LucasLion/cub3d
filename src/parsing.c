/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:31:32 by llion             #+#    #+#             */
/*   Updated: 2023/05/09 15:03:03 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	parse_infos(char **d, t_textures *t)
{
	int		i;

	i = 0;
	while (i < ft_tablen(d))
	{
		printf("d[i]: %s", d[i]);
		if (ft_strlen(d[i]) > 3 && d[i][0] == 'N' && d[i][1] == 'O' && d[i][2] == ' ')
			t->NO = ft_strtrim(d[i] + 3, " ");
		else if (ft_strlen(d[i]) > 3 && d[i][0] == 'S' && d[i][1] == 'O' && d[i][2] == ' ')
			t->SO = ft_strtrim(d[i] + 3, " ");
		else if (ft_strlen(d[i]) > 3 && d[i][0] == 'W' && d[i][1] == 'E' && d[i][2] == ' ')
			t->WE = ft_strtrim(d[i] + 3, " ");
		else if (ft_strlen(d[i]) > 3 && d[i][0] == 'E' && d[i][1] == 'A' && d[i][2] == ' ')
			t->EA = ft_strtrim(d[i] + 3, " ");
		else if (ft_strlen(d[i]) > 2 && d[i][0] == 'F' && d[i][1] == ' ')
			t->fl = ft_strtrim(d[i] + 1, " ");
		else if (ft_strlen(d[i]) > 2 && d[i][0] == 'C' && d[i][1] == ' ')
			t->cl = ft_strtrim(d[i] + 1, " ");
		else if (d[i][0] == '\n' && ++i)
			continue ;
		else
			return (ft_error("Wrong informations"));
		i++;
	}
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
					&& map[i][j] != 'W' && map[i][j] != ' ' \
					&& map[i][j] != '\n')
			{
				ft_error("Wrong element in the map");
				return (0);
			}
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

int	parse_lines(char **map, t_textures *t)
{
	// TODO
	// ca ne marche pas quand ca devrait marcher
	int	i;

	i = 0;
	while (map[i])
		i++;
	printf("i: %d\nlines: %d\n", i, t->lines_before_map);
	if (i != t->lines_before_map)
		return (ft_error("Wrong description"));
	//get_nb_lines_in_map_file(int fd, char **av)

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
	{
		printf("nb players: %d\n", nb_players);
		ft_error("There must be one player");
		return (0);
	}
	return (1);
}

int	parsing(char **file)
{
	int			ret;
	char		**description;
	char		**map;
	t_textures	*t;

	t = ft_calloc(sizeof(t_textures), 1);
	description = get_description(file, t);
	map = get_map(file, t);
	if (parse_lines(map, t) == 0 || parse_infos(description, t) == 0 \
			|| parse_elems(map) == 0 \
			|| parse_borders(map) == 0 || parse_number_players(map) != 1)
		ret = 0;
	else
		ret = 1;
	ft_freetab(description);
	ft_freetab(map);
	free(t->NO);
	free(t->WE);
	free(t->EA);
	free(t->SO);
	free(t->fl);
	free(t->cl);
	free(t);
	return (ret);
}
