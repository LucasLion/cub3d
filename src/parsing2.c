/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:43:14 by llion             #+#    #+#             */
/*   Updated: 2023/07/16 11:28:06 by llion@student    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_file(int argc, char **av)
{
	int	i;

	i = 0;
	if (argc < 2)
		return (ft_error("The program needs map PATH as parameter"));
	else if (argc == 2)
	{
		while (av[1][i])
			i++;
		if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' || av[1][i - 3] != 'c'
			|| av[1][i - 4] != '.')
			return (ft_error("Wrong extension or file"));
		else
		{
			if (open(av[1], O_RDONLY) == -1)
			{
				ft_error("File does not exists");
				return (0);
			}
		}
		return (1);
	}
	else
		return (ft_error("Wrong number of arguments"));
}

int	check_spaces(char c, char **m, int i, int j)
{
	if (c == '0')
	{
		if ((m[i][j + 1] == ' ' || m[i][j + 1] == 0 || m[i][j + 1] == '\n')
			|| (m[i][j - 1] == ' ' || m[i][j - 1] == 0 || m[i][j - 1] == '\n')
			|| (m[i + 1][j] == ' ' || m[i + 1][j] == 0 || m[i + 1][j] == '\n')
			|| (m[i - 1][j] == ' ' || m[i - 1][j] == 0 || m[i - 1][j] == '\n'))
			return (ft_error("Map needs to be closed"));
	}
	return (1);
}

void	parse_loop(t_cub *c, int *i, char **f)
{
	int	j;

	j = 0;
	while (f[*i][j] == ' ')
		j++;
	if (f[*i][j] == '\n' || f[*i][j] == '\0')
	{
		(*i)++;
		return ;
	}
	else if (!((f[*i][j] == 'N' && f[*i][j + 1] == 'O') || (f[*i][j] == 'S'
					&& f[*i][j + 1] == 'O') || (f[*i][j] == 'W' && f[*i][j
					+ 1] == 'E') || (f[*i][j] == 'E' && f[*i][j + 1] == 'A')
				|| (f[*i][j] == 'F' && f[*i][j + 1] == ' ') || (f[*i][j] == 'C'
					&& f[*i][j + 1] == ' ')))
		ft_error("Wrong/Missing parameters");
	else
		c->t->nb_elems++;
}

int	parse_infos(char **f, t_cub *c)
{
	int	i;

	i = 0;
	c->t->nb_elems = 0;
	while (i < ft_tablen(f) && c->t->nb_elems < 6)
		parse_loop(c, &i, f);
	c->nb_line_map_start = i;
	return (1);
}
