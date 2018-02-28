/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:33:48 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/02/15 17:33:49 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#include "stdio.h"
/*
int		width(char **piece)
{
	int i;
	int j;

	i = 0;
	while (piece[i])
	{
		j = 0;
		while (piece[i][j])
			j++;
		i++;
	}
	return (j);
}

int		length(char **piece)
{
	int i;
	int j;

	i = 0;
	while (piece[i])
	{
		j = 0;
		while (piece[i][j])
			j++;
		i++;
	}
	return (i);
}


int		search_place(char **field, char **piece, t_lst *run, int i, int j)
{
	int	i2;
	int j2;
	int	i_temp;
    int i2_temp;
	int connect;

	i2 = 0;
	j2 = 0;
	connect = 0;
    i2_temp = 0;
	i_temp = i;
	while (piece[i2_temp] && piece[i2_temp][j2] != '*')
	{
		j2 = 0;
		while (piece[i2_temp][j2] && piece[i2_temp][j2] != '*')
			j2++;
		if (piece[i2_temp][j2] == '*')
			break;
		i2_temp++;
	}
    i2 = i2_temp;
	while (field[i] && piece[i2])
	{
		j = (i > i_temp) ? 0 : j;
        j2 = (i2 > i2_temp) ? 0 : j2;
		
		while (field[i][j] && piece[i2][j2])
		{
		//		printf("iii22222 %d\n", i);
		//	printf("jjj22222 %d\n", j);
			if (piece[i2][j2] == '*' && (field[i][j] == run->me || field[i][j] == run->me + 32))
				connect++;
			if (piece[i2][j2] == '*' && (field[i][j] == run->me || field[i][j] == run->me + 32 || field[i][j] == '.'))
			{
				j2++;
				j++;
			}
			else if (piece[i2][j2] == '.' && field[i][j] == '.')
			{
				j2++;
				j++;
			}
            else if (piece[i2][j2] == '.' && field[i][j] == run->me)
            {
                j2++;
                j++;
            }
			else if ((piece[i2][j2] == '.' || piece[i2][j2] == '*') && (field[i][j] == run->an 
			|| field[i][j] == run->an + 32))
				return (0);
			else
				return (0);
		}
		i++;
		i2++;
	}
//	printf("here\n");
//	printf("iii %d\n", i);
//	printf("jjj %d\n", j);
	if (i < length(field) && j < width(field))
	{		
//		printf("connect\n");
		return (connect);
	}
	else
		return (0);
//	return (connect);
}

int 	x_piece(char **piece)
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
	return (j2);
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

//char	**set_new_field()

int		module(int a)
{
	if (a < 0)
		a = -1;
	return (a);
}

int		search_closest_x(int i, int j, char **field, t_lst *run)
{
	int i2;
	int	j2;
	int	res_x;
	int res_y;

	i2 = 0;
	res_x = -1;
	res_y = -1;
	while (field[i2])
	{
		j2 = 0;
		while (field[i2][j2])
		{
			if (field[i2][j2] == run->an || field[i2][j2] == run->an + 32)
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

int		compare_xy(int i, int j, char **field, t_lst *run)
{
	if (search_closest_x(i, j, field, run) < search_closest_x(run->best_y, run->best_x, field, run))
		return (1);
	else
		return (0);
}

int		point_num(char **piece)
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

int		logic(char **field, char **piece, t_lst *run)
{
	int	i;
	int	j;
	int connect;

	i = 0;
	while (field[i])
	{
		j = 0;
		while (field[i][j])
		{
			if ((connect = search_place(field, piece, run, i, j)) > 0)
			{
				if (connect == 1 && run->connect == -1 && run->best_x == -1 && run->best_y == -1)
				{
					run->best_x = j;
					run->best_y = i;
					run->connect = connect;
				}
				if (connect > 0 && connect == 1 && compare_xy(i, j, field, run))
				{
					run->connect = connect;
					run->best_x = j;
					run->best_y = i;
				}
			}
			j++;
		}
		i++;
	}
	ft_putnbr(run->best_y - y_piece(piece));
	write(1, " ", 1);
	ft_putnbr(run->best_x - x_piece(piece));
	write(1, "\n", 1);
	return (1);
}

 */