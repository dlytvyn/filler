/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlytvyn.filler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:50:17 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/02/15 11:50:18 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		module(int a)
{
	if (a < 0)
		a = -a;
	return (a);
}

int     plus_i(char **piece)
{
    int i;
    int j;

    i = 0;
    while (piece[i])
    {
        j = 0;
        while (piece[i][j])
        {
            if (piece[i][j] == '*')
                return (i);
            j++;
        }
        i++;
    }
    return (0);
}

int     plus_j(char **piece)
{
    int i;
    int j;
    int res;

    i = 0;
    res = -1;
    while (piece[i])
    {
        j = 0;
        while (piece[i][j])
        {
            if (piece[i][j] == '*')
            {
                res = (res == -1) ? j : res;
                res = (j < res) ? j : res;
            }
            j++;
        }
        i++;
    }
    return (res);
}

int     is_star(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '*')
            return (1);
        i++;
    }
    return (0);
}

int     count_stars(char **piece)
{
    int i;
    int j;
    int count;

    i = 0;
	count = 0;
    while (piece[i])
    {
        j = 0;
        while (piece[i][j])
        {
            if (piece[i][j] == '*')
                count++;
            j++;
        }
        i++;
    }
    return (count);
}

int     ft_try_put(int i, int j, t_lst *run)
{
    int i2;
    int j2;
    int j_plus;
    int i_plus;
    int j_temp;

    i2 = 0;
    j_temp = j;
    i_plus = plus_i(run->piece);
    j_plus = plus_j(run->piece);
    run->stars = count_stars(run->piece);
    while (run->field[i] && run->piece[i2] && run->piece[i2 + i_plus])
    {
        j2 = 0;
        while (run->field[i][j] && run->piece[i2 + i_plus][j2 + j_plus] && run->piece[i2 + i_plus][j2 + j_plus])
        {
	        if (run->piece[i2 + i_plus][j2 + j_plus] == '*')
		        run->stars_count++;
            if (run->piece[i2 + i_plus][j2 + j_plus] == '*' &&
            (run->field[i][j] == run->an || run->field[i][j] == run->an + 32))
                return (0);
            if (run->piece[i2 + i_plus][j2 + j_plus] == '*' &&
            (run->field[i][j] == run->me || run->field[i][j] == run->me + 32))
                run->connect++;
            if (run->connect > 1)
                return (0);
            if (run->connect == 1 && run->stars == run->stars_count)
                return (1);
            j++;
            j2++;
        }
        i++;
        i2++;
        j = j_temp;
    }
    if ((run->piece[i2] && is_star(run->piece[i2])) || run->stars > run->stars_count)
        return (0);
    return ((run->connect == 1) ? 1 : 0);
}

void    search_enemy_up(char **field, t_lst *run, int i2, int j2)
{
	int i;
	int j;

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

void    search_enemy_down(char **field, t_lst *run, int i2, int j2)
{
	int i;
	int j;

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

void    solution(t_lst *run)
{
    int i;
    int j;

    i = 0;
    while (run->field[i])
    {
        j = 0;
        while (run->field[i][j])
        {
	        run->connect = 0;
            run->stars_count = 0;
            if (ft_try_put(i, j, run))
            {
	            search_enemy_down(run->field, run, i, j);
	            search_enemy_up(run->field, run, i, j);
	            if ((run->best_x == 0 && run->best_y == 0) || (module(run->best_y - run->i_en) >= module(i - run->i_en)
	                && module(run->best_x - run->j_en) > module(j - run->j_en)))
	            {
		            run->best_x = j;
		            run->best_y = i;
	            }
            }
            j++;
        }
        i++;
    }
	ft_putnbr(run->best_y - plus_i(run->piece));
	write(1, " ", 1);
	ft_putnbr(run->best_x - plus_j(run->piece));
	write(1, "\n", 1);
}

void    set_initial_data(t_lst *run)
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

void	ft_filler(t_lst *run)
{
    int fd;
    char *line;

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


