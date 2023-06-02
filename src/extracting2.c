/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:59:49 by llion             #+#    #+#             */
/*   Updated: 2023/06/01 15:28:21 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	split_and_convert(char *line, uint8_t transp)
{
	char **tmp;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	
	tmp = ft_split(line, ',');
	red = ft_atoi(tmp[0]);
	green = ft_atoi(tmp[1]);
	blue = ft_atoi(tmp[2]);
	tmp = NULL;
	return (rgb_to_hexa(red, green, blue, transp));
}

int get_textures_wall(t_cub *c, char **file, t_textures *t)
{
	int i = 0;
	int a = 0;
	char	**line;

	while(i < c->nb_line_map_start)
	{
		line = ft_split(file[i], ' ');
		if (ft_strncmp(line[0], "NO", 2) == 0)
		{
			t->NO = ft_strtrim(line[1], "\n");
			a++;
		}
		else if (ft_strncmp(line[0], "SO", 2) == 0)
		{
			t->SO = ft_strtrim(line[1], "\n");
			a++;
		}
		else if (ft_strncmp(line[0], "WE", 2) == 0)
		{
			t->WE = ft_strtrim(line[1], "\n");
			a++;
		}
		else if (ft_strncmp(line[0], "EA", 2) == 0)
		{
			t->EA = ft_strtrim(line[1], "\n");
			a++;
		}
		ft_freetab(line);
		i++;
	}
	if (a == 4)
		return (1);
	return (0);
}

int get_colors(t_cub *c, char **file, t_textures *t)
{
	int		i;
	int		a;
	char	**line;

	i = 0;
	a = 0;
	while(i < c->nb_line_map_start)
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
	if (a == 2)
		return (1);
	return (0);
}
/*
int get_colors(char **file, t_textures *t)
{
	int i = 0;
	int a = 0;

	while(file[i])
	{
		if (file[i][0] == 'F')
		{
			t->floor = split_and_convert(&(file[i][2]), 255);
			a++; 
		}
		if (file[i][0] == 'C')
		{
			t->ceiling = split_and_convert(&(file[i][2]), 255);
			a++; 
		}
		i++;
	}
	if (a == 2)
		return (1);
	return (0);
}
*/
uint32_t	rgb_to_hexa(uint8_t red, uint8_t green, uint8_t blue, uint8_t transp)
{
	return ((red << 24) | (green  << 16) | (blue << 8) | (transp));
}

t_textures	*get_textures(t_cub *c, char **file)
{
	t_textures	*tmp;

	tmp = ft_calloc(1, sizeof(t_textures));
	if (get_textures_wall(c, file, tmp) == 0)
		printf("probleme avec les textures\n");
	if (get_colors(c, file, tmp) == 0)
		printf("probleme avec les couleurs\n");
	return (tmp);	
}
