/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:59:49 by llion             #+#    #+#             */
/*   Updated: 2023/06/07 14:40:38 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	split_and_convert(char *line, uint8_t transp)
{
	char	**tmp;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	int		i;

	i = 0;
	tmp = ft_split(line, ',');
	while (tmp[i])
		i++;
	if (i != 3)
	{
		ft_freetab(tmp);
		return (0);
	}
	red = ft_atoi(tmp[0]);
	green = ft_atoi(tmp[1]);
	blue = ft_atoi(tmp[2]);
	ft_freetab(tmp);
	tmp = NULL;
	return ((red << 24) | (green << 16) | (blue << 8) | (transp));
}

void	trim(int *count, char **direction, char *texture, int *err)
{
	int	fd;

	*direction = ft_strtrim(texture, "\n");
	fd = open(*direction, O_RDONLY);
	if (fd == -1)
	{
		printf("Invalid file\n");
		close(fd);
		free(*direction);
		*err = 1;
		return ;
	}
	close(fd);
	(*count)++;
}

int	get_textures_wall(t_cub *c, char **file, t_textures *t, int *err)
{
	int		i;
	int		count;
	char	**line;

	i = 0;
	count = 0;
	while (i < c->nb_line_map_start)
	{
		line = ft_split(file[i], ' ');
		if (ft_strncmp(line[0], "NO", 2) == 0)
			trim(&count, &t->no, line[1], err);
		else if (ft_strncmp(line[0], "SO", 2) == 0)
			trim(&count, &t->so, line[1], err);
		else if (ft_strncmp(line[0], "WE", 2) == 0)
			trim(&count, &t->we, line[1], err);
		else if (ft_strncmp(line[0], "EA", 2) == 0)
			trim(&count, &t->ea, line[1], err);
		ft_freetab(line);
		i++;
	}
	if (count == 4)
		return (1);
	return (0);
}

int	get_colors(t_cub *c, char **file, t_textures *t)
{
	int		i;
	int		a;
	char	**line;

	i = 0;
	a = 0;
	while (i < c->nb_line_map_start)
	{
		line = ft_split(file[i], ' ');
		if (line[0][0] == 'F')
		{
			t->floor = split_and_convert(line[1], 255);
			a++;
		}
		else if (line[0][0] == 'C')
		{
			t->ceiling = split_and_convert(line[1], 255);
			a++;
		}
		ft_freetab(line);
		i++;
	}
	if (a == 2 && t->floor != 0 && t->ceiling != 0)
		return (1);
	return (0);
}

t_textures	*get_textures(t_cub *c, char **file)
{
	t_textures	*tmp;
	int			error;

	error = 0;
	tmp = ft_calloc(1, sizeof(t_textures));
	if (get_textures_wall(c, file, tmp, &error) == 0 || error == 1)
	{
		printf("Wrong textures\n");
		free(tmp);
		return (NULL);
	}
	if (get_colors(c, file, tmp) == 0)
	{
		printf("Wrong colors\n");
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
