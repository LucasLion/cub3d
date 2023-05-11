/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:59:49 by llion             #+#    #+#             */
/*   Updated: 2023/05/11 17:55:24 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
int	get_nb_line_map_start(char **f, t_cub *c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < ft_tablen(f) && k < 6)
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
			k++;
		i++;
	}
	return (i);
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

char	**get_map(char **f, int i)
{
	char	**map;
	int		j;
	
	j = 0;
	map = ft_calloc(ft_tablen(f) - i + 1, sizeof(char *));
	if (!map)
		return (0);
	while (f[i])
	{
		if (f[i][0] == '\n')
			i++;
		else 
		{
			map[j] = ft_strdup(f[i]);
			i++;
			j++;
		}
	}
	return (map);
}
