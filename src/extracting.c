/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:59:49 by llion             #+#    #+#             */
/*   Updated: 2023/05/08 17:20:29 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	get_nb_lines_in_map_file(int fd, char **av)
{
	int		num_lines;
	char	*line;

	num_lines = 0;
	fd = open(av[1], O_RDONLY);
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

int	get_nb_lines_before_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// TODO 
	// faire en sorte que les lignes qui n'ont rien a faire dans le fichier fassent une erreur
	while (map[i])
	{
		if (map[i][0] == 'R' || map[i][0] == 'N' || map[i][0] == 'S' \
			|| map[i][0] == 'W' || map[i][0] == 'E' || map[i][0] == 'F' \
			|| map[i][0] == 'C' || map[i][0] == '\n')
		{
			j++;
		}
		i++;
	}
	return (j);
}

char	**get_file(int argc, char **av)
{
	char	**map;
	int		i;
	char	*line;
	int		fd;

	i = 0;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_error("File does not exists");
		return (NULL);
	}
	if (parse_file(argc, av) == 0)
		return (0);
	map = ft_calloc(sizeof(char *), get_nb_lines_in_map_file(fd, av) + 1);
	while (i < get_nb_lines_in_map_file(fd, av))
	{
		line = get_next_line(fd);
		map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	return (map);
}

char	**get_description(char **file, t_textures *t)
{
	int		i;
	int		j;
	char	**description;
	char	*tmp;

	i = 0;
	j = 0;
	t->lines_before_map = get_nb_lines_before_map(file);
	description = ft_calloc(sizeof(char *), t->lines_before_map + 1);
	if (!description)
		return (NULL);
	while (file[i])
	{
		if (file[i][0] == 'R' || file[i][0] == 'N' || file[i][0] == 'S' \
			|| file[i][0] == 'W' || file[i][0] == 'E' || file[i][0] == 'F' \
			|| file[i][0] == 'C' || file[i][0] == '\n')
		{
			tmp = ft_strdup(file[i]);
			description[j] = ft_strtrim(tmp, " ");
			free(tmp);
			j++;
		}
		i++;
	}
	printf("nblinebfmap: %d\n", t->lines_before_map);
	return (description);
}

char	**get_map(char **file, t_textures *t)
{
	int		i;
	int		j;
	char	**map;

	i = t->lines_before_map;
	j = 0;
	map = ft_calloc(sizeof(char *), ft_tablen(file) + 1);
	if (!map)
		return (NULL);
	while (file[i])
	{
		if (file[i][0] != 'R' && file[i][0] != 'N' && file[i][0] != 'S' \
			&& file[i][0] != 'W' && file[i][0] != 'E' && file[i][0] != 'F' \
			&& file[i][0] != 'C' && file[i][0] != '\n')
		{
			map[j] = ft_strdup(file[i]);
			j++;
		}
		i++;
	}
	for (int i = 0; i < ft_tablen(map); i++)
		printf("%s", map[i]);
	return (map);
}
