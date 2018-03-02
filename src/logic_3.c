/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:16:51 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/02 17:16:52 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		module(int a)
{
	if (a < 0)
		a = -a;
	return (a);
}

int		plus_i(char **piece)
{
	int	i;
	int	j;

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

int		plus_j(char **piece)
{
	int	i;
	int	j;
	int	res;

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

int		st(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

int		count_stars(char **piece)
{
	int	i;
	int	j;
	int	count;

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
