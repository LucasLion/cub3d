/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:59:49 by llion             #+#    #+#             */
/*   Updated: 2023/05/10 21:02:49 by llion            ###   ########.fr       */
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

int	get_map(char **f, t_textures *t, int i)
{
	int	j;
	
	j = 0;
	t->map = ft_calloc(ft_tablen(f) - i + 1, sizeof(char *));
	if (!t->map)
		return (0);
	while (f[i])
	{
		if (f[i][0] == '\n')
			i++;
		else 
		{
			t->map[j] = ft_strdup(f[i]);
			i++;
			j++;
		}
	}
	return (1);
}
