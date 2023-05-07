/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:37:53 by llion             #+#    #+#             */
/*   Updated: 2023/05/07 17:13:09 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	main(void)
{
	char	**map;
	//char	**description;
	char	**file;

	file = get_file();
	//description = get_description(file);
	map = get_map(file);
	for (int i = 0; i < ft_tablen(map); i++)
		printf("%s", map[i]);
	return (0);
}
