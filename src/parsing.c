/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:31:32 by llion             #+#    #+#             */
/*   Updated: 2023/06/04 11:50:58 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//int rechercher_informations_valides(char **f, t_cub *c, int i)
//{
//    int j = 0;
//    
//    while (f[i][j] == ' ')
//        j++;
//    
//	printf("i = %d\n", i);
//	printf("f[i][j] = %c\n", f[i][j]);
//	printf("c->t->nb_elems = %d\n", c->t->nb_elems);
//    if (f[i][j] == '\n' || f[i][j] == '\0')
//        return i + 1;
//    else if (!((f[i][j] == 'N' && f[i][j + 1] == 'O') || (f[i][j] == 'S' && f[i][j + 1] == 'O') ||
//               (f[i][j] == 'W' && f[i][j + 1] == 'E') || (f[i][j] == 'E' && f[i][j + 1] == 'A') ||
//               (f[i][j] == 'F' && f[i][j + 1] == ' ') || (f[i][j] == 'C' && f[i][j + 1] == ' ')))
//        return ft_error("Paramètres incorrects/manquants");
//	else 
//		c->t->nb_elems++;
//    return (i + 1);
//}
//
//int parse_infos(char **f, t_cub *c)
//{
//    int i = 1;
//
//    c->t->nb_elems = 0;
//    while (i < ft_tablen(f) + 1 && c->t->nb_elems < 6)
//    {
//        i = rechercher_informations_valides(f, c, i);
//        if (i == 0)
//            return 0;
//    }
//    c->nb_line_map_start = i;
//    return 1;
//}
int	parse_infos(char **f, t_cub *c)
{
	int		i;
	int		j;

	i = 0;
	c->t->nb_elems = 0;
	while (i < ft_tablen(f) && c->t->nb_elems < 6)
	{
		j = 0;
		while (f[i][j] == ' ')
			j++;
		if (f[i][j] == '\n' || f[i][j] == '\0')
		{
			i++;
			continue ;
		}
		else if (!((f[i][j] == 'N' && f[i][j + 1] == 'O') || (f[i][j] == 'S' \
				&& f[i][j + 1] == 'O') || (f[i][j] == 'W' \
				&& f[i][j + 1] == 'E') || (f[i][j] == 'E' \
				&& f[i][j + 1] == 'A') || (f[i][j] == 'F' \
				&& f[i][j + 1] == ' ') || (f[i][j] == 'C' \
				&& f[i][j + 1] == ' ')))
			return (ft_error("Wrong/Missing parameters"));
		else
			c->t->nb_elems++;
		i++;
	}
	c->nb_line_map_start = i;
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
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2' && map[i][j] != 'N' \
					&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != '\0'\
					&& map[i][j] != 'W' && map[i][j] != ' ' && map[i][j] != '\n')
				return (ft_error("Invalid map (foreign chars)"));
			j++;
		}
		i++;
	}
	return (1);
}

int	check_spaces(char c, char **m, int i, int j)
{
	if (c == '0')
	{
		if ((m[i][j + 1] == ' ' || m[i][j + 1] == 0 || m[i][j + 1] == '\n') \
			|| (m[i][j - 1] == ' ' || m[i][j - 1] == 0 || m[i][j - 1] == '\n') \
			|| (m[i + 1][j] == ' ' || m[i + 1][j] == 0 || m[i + 1][j] == '\n') \
			|| (m[i - 1][j] == ' ' || m[i - 1][j] == 0 || m[i - 1][j] == '\n'))
			return (ft_error("Map needs to be closed"));
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
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' \
					|| map[i][j] == 'W')
				nb_players++;
			j++;
		}
		i++;
	}
	if (nb_players != 1)
		return (ft_error("Wrong number of players"));
	return (1);
}

int	parsing(char **file, t_cub *c)
{
	if (parse_infos(file, c) == 0 || parse_elems_in_map(c->map) == 0 \
			|| parse_borders(c->map) == 0 || parse_number_players(c->map) == 0)
		return (0);
	return (1);
}
