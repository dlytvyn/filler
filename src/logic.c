/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:14:14 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/02 17:14:15 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	print_res(t_link *run)
{
	ft_printf("%d %d\n", run->best_y - plus_i(run->piece),
		run->best_x - plus_j(run->piece));
}

void	solution_add(t_link *run, int i, int j, int distance)
{
	if ((run->best_x == 0 && run->best_y == 0) || distance <= run->dist)
	{
		if (run->rows > 35 && run->columns > 35 &&
			(module(run->rows / 2 - run->best_y) > module(run->rows / 2 - i)
				|| j < run->best_x))
		{
			run->best_x = j;
			run->best_y = i;
			run->dist = module(i - run->i_en) + module(j - run->j_en);
		}
		else if ((run->best_x == 0 && run->best_y == 0)
			|| ((run->rows - i < run->rows / 2) && i > run->best_y))
		{
			run->best_x = j;
			run->best_y = i;
			run->dist = module(i - run->i_en) + module(j - run->j_en);
		}
		else
		{
			run->best_x = j;
			run->best_y = i;
			run->dist = module(i - run->i_en) + module(j - run->j_en);
		}
	}
}

void	solution(t_link *run)
{
	int	i;
	int	j;
	int	distance;

	i = 0;
	while (run->field[i])
	{
		j = 0;
		while (run->field[i][j])
		{
			distance = 0;
			run->connect = 0;
			run->stars_count = 0;
			if (ft_try_put(i, j, run))
			{
				search_enemy_down(run->field, run, i, j);
				search_enemy_up(run->field, run, i, j);
				distance = module(i - run->i_en) + module(j - run->j_en);
				solution_add(run, i, j, distance);
			}
			j++;
		}
		i++;
	}
	print_res(run);
}

void	set_initial_data(t_link *run)
{
	run->best_x = 0;
	run->best_y = 0;
	run->p_col = 0;
	run->p_rows = 0;
	run->dist = 0;
	run->i_en = 0;
	run->j_en = 0;
	run->connect = 0;
	run->stars = 0;
	run->stars_count = 0;
	ft_free(run->piece);
	ft_free(run->field);
}

void	ft_filler(t_link *run)
{
	int		fd;
	char	*line;

	fd = open("/Users/dlytvyn/Filler/map00", O_RDONLY);
	fd = 0;
	if (fd < 0)
		exit(0);
	run->me = (get_player(fd) == 1) ? 'O' : 'X';
	run->an = (run->me == 'O') ? 'X' : 'O';
	while (get_next_line(fd, &line))
	{
		if (ft_strstr(line, "Plateau") != 0)
		{
			run->field = get_field(fd, run, line);
			run->piece = get_piece(fd, run);
			solution(run);
			set_initial_data(run);
		}
	}
}
