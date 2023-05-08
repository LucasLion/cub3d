/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:31:32 by llion             #+#    #+#             */
/*   Updated: 2023/05/08 16:29:57 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	parse_file(int argc, char **av)
{
	int		i;

	i = 0;
	if (argc != 2)
		return (ft_error("The program needs map PATH as parameter"));
	while (av[1][i])
		i++;
	if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' || av[1][i - 3] != 'c' \
			|| av[1][i - 4] != '.')
		return (ft_error("Wrong extension"));
	return (1);
}

int	parse_infos(char **d, t_textures *t)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < ft_tablen(d))
	{
		tmp = d[i];
		if (ft_strlen(tmp) > 3 && tmp[0] == 'N' && tmp[1] == 'O' && tmp[2] == ' ')
			t->NO = ft_strtrim(tmp + 3, " ");
		else if (ft_strlen(tmp) > 3 && tmp[0] == 'S' && tmp[1] == 'O' && tmp[2] == ' ')
			t->SO = ft_strtrim(tmp + 3, " ");
		else if (ft_strlen(tmp) > 3 && tmp[0] == 'W' && tmp[1] == 'E' && tmp[2] == ' ')
			t->WE = ft_strtrim(tmp + 3, " ");
		else if (ft_strlen(tmp) > 3 && tmp[0] == 'E' && tmp[1] == 'A' && tmp[2] == ' ')
			t->EA = ft_strtrim(tmp + 3, " ");
		else if (ft_strlen(tmp) > 2 && tmp[0] == 'F' && tmp[1] == ' ')
			t->fl = ft_strtrim(tmp + 1, " ");
		else if (ft_strlen(tmp) > 2 && tmp[0] == 'C' && tmp[1] == ' ')
			t->cl = ft_strtrim(tmp + 1, " ");
		else if (tmp[0] == '\n' && ++i)
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
					&& map[i][j] != 'W' && map[i][j] != ' ' && map[i][j] != '\n')
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
	if (parse_infos(description, t) == 0 || parse_elems(map) == 0 \
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
