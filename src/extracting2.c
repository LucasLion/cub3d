/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:59:49 by llion             #+#    #+#             */
/*   Updated: 2023/05/29 16:21:40 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// TODO corriger l'endroit ou on calcule le nombre de lignes avant la map

int get_textures_wall(char **file, t_textures *t)
{
	int i = 0;
	int a = 0;

	while(file[i])
	{
		if (file[i][1] == 'O' || file[i][1] == 'E' || file [i][1] == 'A')
		{
			if (file[i][0] == 'N' && file[i][1] == 'O')	
				t->NO = ft_strdup(&(file[i][3]));
			if (file[i][0] == 'S' && file[i][1] == 'O')
				t->SO = ft_strdup(&(file[i][3]));
			if (file[i][0] == 'W' && file[i][1] == 'E')
				t->WE = ft_strdup(&(file[i][3]));	
			if (file[i][0] == 'E' && file[i][1] == 'A')
				t->EA = ft_strdup(&(file[i][3]));
			a++;
		}
		i++;
	}
	if (a == 4)
		return (1);
	return (0);
}

uint32_t	rgb_to_hexa(uint8_t red, uint8_t green, uint8_t blue, uint8_t transp)
{
	return ((red << 24) | (green  << 16) | (blue << 8) | (transp));
}


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

t_textures *get_textures(char **file)
{
	t_textures *tmp;
	
	tmp = ft_calloc(1, sizeof(t_textures));
	if (get_textures_wall(file, tmp) == 0)
		printf("probleme avec les textures\n");
	if (get_colors(file, tmp) == 0)
		printf("probleme avec les couleurs\n");
	return (tmp);
	
}
