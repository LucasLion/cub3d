/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:31:32 by llion             #+#    #+#             */
/*   Updated: 2023/05/10 23:38:06 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"


int	parse_infos(char **f, t_textures *t)
{
	int		i;
	int		j;

	i = 0;
	t->nb_elems = 0;
	while (i < ft_tablen(f) && t->nb_elems < 6)
	{
		j = 0;
		while (f[i][j] == ' ')
			j++;
		if (f[i][j] == '\n')
			i++;
		if (!((f[i][j] == 'N' && f[i][j + 1] == 'O') || (f[i][j] == 'S' \
				&& f[i][j + 1] == 'O') || (f[i][j] == 'W' \
				&& f[i][j + 1] == 'E') || (f[i][j] == 'E' \
				&& f[i][j + 1] == 'A') || (f[i][j] == 'F' \
				&& f[i][j + 1] == ' ') || (f[i][j] == 'C' \
				&& f[i][j + 1] == ' ')))
			return (0);
		else
			t->nb_elems++;
		i++;
	}
	if (!(get_map(f, t, i)))
		return (0);
	return (1);
}


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

int	check_spaces(char c, char **m, int i, int j)
{
	if (c == ' ')
	{
		if ((m[i][j + 1] != '1' && m[i][j + 1] != ' ' && m[i][j + 1] != 0) \
			|| (m[i][j - 1] != '1' && m[i][j - 1] != ' ' && m[i][j - 1] != 0) \
			|| (m[i + 1][j] != '1' && m[i + 1][j] != ' ' && m[i + 1][j] != 0) \
			|| (m[i - 1][j] != '1' && m[i - 1][j] != ' ' && m[i - 1][j] != 0))
		{
			printf("i = %d, j = %d\n", i, j);
			printf("m[i][j + 1] = ---%c---\n", m[i][j + 1]);
			printf("m[i][j - 1] = ---%c---\n", m[i][j - 1]);
			printf("m[i + 1][j] = ---%c---\n", m[i + 1][j]);
			printf("m[i - 1][j] = ---%c---\n", m[i - 1][j]);
			return (0);
		}
	}
	return (1);
}

int	parse_borders(char **map)
{
	int		i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (map[i][j] == '\n')
			i++;
		while (map[i][j])
		{
			if (i == 0 || i == ft_tablen(map) - 1 || j == 0 \
					|| j == (int)ft_strlen(map[i]) - 2)
			{
				// TODO
				// lorsque un zero depasse du cadre il ne trouve pas l'erreur
				if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\n')	
					return (0);
			}
			else if (check_spaces(map[i][j], map, i, j) == 0)
				return (0);
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

int	parsing(char **file, t_textures *t)
{
	if (parse_infos(file, t) == 0 || parse_elems_in_map(t->map) == 0 \
			|| parse_borders(t->map) == 0 || parse_number_players(t->map) != 1)
		return (0);
	return (1);
}
