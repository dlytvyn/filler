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

#include "stdio.h"
#include <fcntl.h>


int		module(int a)
{
	if (a < 0)
		a = -1;
	return (a);
}

int		search_closest_x(int i, int j, t_lst *run)
{
	int i2;
	int	j2;
	int	res_x;
	int res_y;

	i2 = 0;
	res_x = -1;
	res_y = -1;
	while (run->field[i2])
	{
		j2 = 0;
		while (run->field[i2][j2])
		{
			if (run->field[i2][j2] == run->an || run->field[i2][j2] == run->an + 32)
			{
				if (res_x == -1)
					res_x = module(i2 - i);
				if (res_y == -1)
					res_y = module(j2 - j);
				res_x = module(i2 - i) < res_x ? module(i2 - i) : res_x;
				res_y = module(j2 - j) < res_y ? module(j2 - j) : res_y;
			}
			j2++;
		}
		i2++;
	}
	return (res_x + res_y);
}

int		compare_xy(int i, int j, t_lst *run)
{
	if (search_closest_x(i, j, run) < search_closest_x(run->best_y, run->best_x, run))
		return (1);
	else
		return (0);
}






int 	y_piece(char **piece)
{
	int	i2;
	int j2;

	i2 = 0;
	j2 = 0;
	while (piece[i2] && piece[i2][j2] != '*')
	{
		j2 = 0;
		while (piece[i2][j2] && piece[i2][j2] != '*')
			j2++;
		if (piece[i2][j2] == '*')
			break;
		i2++;
	}
	return (i2);
}

int     add(char **piece)
{
	int i;
	int j;
	int res;

	i = 0;
	while (piece[i])
	{
		j = 0;
		while (piece[i][j])
		{
			if (piece[i][j] == '*')
			{
				res = j;
				return (res);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int     distance(char **piece)
{
    int i;
    int j;
	int res;

    i = 0;
	res = add(piece);
    while (piece[i])
    {
        j = 0;
        while (piece[i][j])
        {
			if (piece[i][j] == '*')
				res = (j < res) ? j : res;
            j++;
        }
        i++;
    }
	return (res);
}


void	print(char **res)
{
	int i;

	i = 0;
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
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

int     try(t_lst *run, int i, int j)
{
    int plus;
	int i2;
	int j2;
	int connect;
    int stars;
    int count;
	int i_temp;
	int j_temp;

    plus = distance(run->piece);
	i2 = 0;
    count = 0;
	i_temp = i;
	j_temp = j;
	connect = 0;
    stars = count_stars(run->piece);
	//print(run->field);
	//write(1, "\n", 1);
	while (run->field[i] && run->piece[i2 + y_piece(run->piece)])
	{
		j = j_temp;
		j2 = 0;
		while (run->field[i][j] && run->piece[i2 + y_piece(run->piece)][j2 + plus])
		{
			if (j + 1 == run->columns && run->piece[i2 + y_piece(run->piece)][j2 + plus + 1])
			{
				if (run->piece[i2 + y_piece(run->piece)][j2 + plus + 1] == '*')
					return (-1);
			}
			if (i + 1 == run->rows && run->piece[i2 + y_piece(run->piece) + 1])
			{
				if (run->piece[i2 + y_piece(run->piece) + 1][j2 + plus] == '*')
					return (-1);
			}
            if (count == stars && connect == 0)
                return (-1);
            if (count == stars && connect == 1)
                return (1);
			if (run->piece[i2 + y_piece(run->piece)][j2 + plus] == '*' && (run->field[i][j] == run->me || run->field[i][j] == run->me + 32))
				connect++;
            if (connect > 1)
                return (-1);
			if (run->piece[i2 + y_piece(run->piece)][j2 + plus] == '*' && (run->field[i][j] == '.'
                || run->field[i][j] == run->me || run->field[i][j] == run->me + 32))
			{
                count++;
				j++;
				j2++;
			}
			else if (run->piece[i2 + y_piece(run->piece)][j2 + plus] == '.' && (run->field[i][j] == '.'
                    || run->field[i][j] == run->me
			        || run->field[i][j] == run->me + 32
			        || run->field[i][j] == run->an
                    || run->field[i][j] == run->an + 32))
			{
				j++;
				j2++;
			}
			else if (run->piece[i2 + y_piece(run->piece)][j2 + plus] == '*'
                    && (run->field[i][j] == run->an
                    || run->field[i][j] == run->an + 32))
				return (-1);
		}

		i++;
		i2++;
	}
	return (connect);
}

void    solution(t_lst *run)
{
    int i;
    int j;
	int connect;

    i = 0;
    while (run->field[i])
    {
        j = 0;
        while (run->field[i][j])
        {
            if ((connect = try(run, i, j)) == 1 && compare_xy(i, j, run) == 1
                && module(run->columns - j) < module(run->columns - run->best_x)
                && module(run->rows - i) < module(run->rows - run->best_y))
            {
	            run->best_x = j;
	            run->best_y = i;
	            run->connect = connect;
            }
            j++;
        }
        i++;
    }
	ft_putnbr(run->best_y - y_piece(run->piece));
	write(1, " ", 1);
	ft_putnbr(run->best_x - distance(run->piece));
	write(1, "\n", 1);
}












int		get_player(int fd)
{
    char	*line;
    int		res;

    res = 0;
    line = NULL;
    get_next_line(fd, &line);
    if (ft_strstr(line, "dlytvyn.filler") != 0 && ft_strstr(line, "$$$ exec p1") != 0)
        res = 1;
    ft_strdel(&line);
    return (res);
}

char	**get_field(int fd, t_lst *run)
{
    int		i;
    char	**array;
    char	*line;

    i = 0;
    line = NULL;
    array = (char**)malloc(sizeof(char*) * (run->rows + 1));
    while (i < run->rows)
    {
        get_next_line(fd, &line);
        array[i] = ft_strnew(run->columns + 1);
        array[i] = ft_strcpy(array[i], line + 4);
        array[i][run->columns] = '\0';
        ft_strdel(&line);
        i++;
    }
    array[i] = NULL;
    return (array);
}

char	**get_piece(int fd, t_lst *run)
{
    int		i;
    char	**array;
    char	*line;

    i = 0;
    line = NULL;
    array = (char**)malloc(sizeof(char*) * (run->p_rows + 1));
    while (i < run->p_rows)
    {
        get_next_line(fd, &line);
        array[i] = ft_strnew(run->p_col + 1);
        array[i] = ft_strcpy(array[i], line);
        array[i][run->p_col] = '\0';
        ft_strdel(&line);
        i++;
    }
    array[i] = NULL;
    return (array);
}

void    ft_free(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        ft_strdel(&array[i]);
        i++;
    }
}

void	ft_filler(t_lst *run)
{
    int fd;
    char *line;
    int   i;

    //fd = open("/Users/dlytvyn/Filler/map00", O_RDONLY);
    fd = 0;
    if (fd < 0)
        exit(0);
    run->me = (get_player(fd) == 1) ? 'O' : 'X';
    run->an = (run->me == 'O') ? 'X' : 'O';
    while (get_next_line(fd, &line))
    {
        if (ft_strstr(line, "Plateau") != 0)
        {
            i = 0;
            while (line[i] < '1' || line[i] > '9')
                i++;
            run->rows = ft_atoi(line + i);
            while (line[i] != ' ')
                i++;
            i++;
            run->columns = ft_atoi(line + i);
            ft_strdel(&line);
            get_next_line(fd, &line);
            ft_strdel(&line);
            run->field = get_field(fd, run);
            get_next_line(fd, &line);
            i = 0;
            while (line[i] < '1' || line[i] > '9')
                i++;
            run->p_rows = ft_atoi(line + i);
            while (line[i] != ' ')
                i++;
            i++;
            run->p_col = ft_atoi(line + i);
            ft_strdel(&line);
            run->piece = get_piece(fd, run);
            solution(run);
            run->best_x = -1;
            run->best_y = -1;
            run->connect = -1;
            run->p_col = 0;
            run->p_rows = 0;
            ft_free(run->piece);
            ft_free(run->field);
        }
    }
}

t_lst	*new_list(void)
{
    t_lst	*run;

    run = (t_lst*)malloc(sizeof(t_lst));
    run->an = 0;
    run->me = 0;
    run->best_x = -1;
    run->best_y = -1;
    run->columns = 0;
    run->rows = 0;
    run->p_col = 0;
    run->p_rows = 0;
    run->connect = -1;
    run->field = NULL;
    run->piece = NULL;
    return (run);
}

int	main()
{
    t_lst *run;

    run = new_list();
    ft_filler(run);
    return (1);
}
