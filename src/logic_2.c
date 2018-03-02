/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlytvyn.filler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:50:17 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/02 16:49:18 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	set_data(int *i_plus, int *j_plus, int *i2, t_link *run)
{
	*i2 = 0;
	*i_plus = plus_i(run->piece);
	*j_plus = plus_j(run->piece);
	run->stars = count_stars(run->piece);
}

int		ft_try_put(int i, int j, t_link *run)
{
	int	i2;
	int	j2;
	int	j_plus;
	int	i_plus;
	int	j_temp;

	j_temp = j;
	set_data(&i_plus, &j_plus, &i2, run);
	while (run->field[i] && run->piece[i2] && run->piece[i2 + i_plus])
	{
		j2 = 0;
		while (ARR5 && ARR6)
		{
			(run->piece[i2 + i_plus][j2 + j_plus] == '*') && run->stars_count++;
			(ARR1 && ARR2) && run->connect++;
			if (run->connect > 1 || (ARR3 && ARR4))
				return (0);
			if (run->connect == 1 && run->stars == run->stars_count)
				return (1);
			++j && ++j2;
		}
		++i && ++i2 && (j = j_temp);
	}
	if ((run->piece[i2] && st(run->piece[i2])) || run->stars > run->stars_count)
		return (0);
	return ((run->connect == 1) ? 1 : 0);
}

void	search_enemy_up(char **field, t_link *run, int i2, int j2)
{
	int	i;
	int	j;

	i = i2;
	while (i >= 0)
	{
		j = j2;
		while (j >= 0)
		{
			if (field[i][j] == run->an || field[i][j] == run->an + 32)
			{
				if (module(j2 - run->i_en) + module(i2 - run->j_en) >
						module(i2 - i) + module(j2 - j))
				{
					run->i_en = i;
					run->j_en = j;
				}
				return ;
			}
			j--;
		}
		i--;
	}
}

void	search_enemy_down(char **field, t_link *run, int i2, int j2)
{
	int	i;
	int	j;

	i = i2;
	while (field[i])
	{
		j = j2;
		while (field[i][j])
		{
			if (field[i][j] == run->an || field[i][j] == run->an + 32)
			{
				run->i_en = i;
				run->j_en = j;
				return ;
			}
			j++;
		}
		i++;
	}
}
