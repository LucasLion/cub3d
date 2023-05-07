/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:59:49 by llion             #+#    #+#             */
/*   Updated: 2023/05/07 17:44:10 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	get_nb_lines_in_map_file(int fd)
{
	int		num_lines;
	char	*line;

	num_lines = 0;
	fd = open("maps/map1.cub", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		num_lines++;
		line = get_next_line(fd);
	}
	free(line);
	return (num_lines);
}

char	**get_file()
{
	char	**map;
	int		i;
	char	*line;
	int		fd;

	fd = open("maps/map1.cub", O_RDONLY);
	i = 0;
	map = ft_calloc(sizeof(char *), get_nb_lines_in_map_file(fd) + 1);
	while (i < get_nb_lines_in_map_file(fd))
	{
		line = get_next_line(fd);
		map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	return (map);
}

char **get_description(char **map)
{
	int i;
	int j;
	char **description;

	i = 0;
	j = 0;
	description = ft_calloc(sizeof(char *), 7);
	if (!description)
		return (NULL);
	while (map[i])
	{
		if (map[i][0] == 'R' || map[i][0] == 'N' || map[i][0] == 'S' || map[i][0] == 'W' || map[i][0] == 'E' || map[i][0] == 'F' || map[i][0] == 'C')
		{
			description[j] = ft_strdup(map[i]);
			j++;
		}
		i++;
	}
	return (description);
}

char	**get_map(char **file)
{
	int i;
	int j;
	char **map;

	i = 0;
	j = 0;
	map = ft_calloc(sizeof(char *), ft_tablen(file) + 1);
	if (!map)
		return (NULL);
	while (file[i])
	{
		if (file[i][0] != 'R' && file[i][0] != 'N' && file[i][0] != 'S' && file[i][0] != 'W' && file[i][0] != 'E' && file[i][0] != 'F' && file[i][0] != 'C')
		{
			map[j] = ft_strdup(file[i]);
			j++;
		}
		i++;
	}
	return (map);
}
