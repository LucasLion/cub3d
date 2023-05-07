/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:31:32 by llion             #+#    #+#             */
/*   Updated: 2023/05/07 17:42:48 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"


int	parse_description(char **description)
{
	// TODO 
	(void)description;
	return (1);
}


int	parse_map(char **map)
{
	// TODO 
	(void)map;
	return (1);
}

int	parsing(char **file)
{
	char	**description;
	char	**map;

	description = get_description(file);
	map = get_map(file);
	if (parse_description(description) == 0 || parse_map(map) == 0)
	{
		ft_freetab(description);
		ft_freetab(map);
		return (0);
	}
	ft_freetab(description);
	ft_freetab(map);
	return (1);
}
