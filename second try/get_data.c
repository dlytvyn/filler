/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:34:23 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/02/28 11:34:24 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

char	**get_field(int fd, t_lst *run, char *line)
{
    int		i;
    char	**array;

	i = 9;
	run->rows = ft_atoi(line + 8);
	while (line[i] != ' ')
		i++;
	i++;
	run->columns = ft_atoi(line + i);
	ft_strdel(&line);
	get_next_line(fd, &line);
	ft_strdel(&line);
    array = (char**)malloc(sizeof(char*) * (run->rows + 1));
	i = 0;
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

	get_next_line(fd, &line);
	i = 7;
	run->p_rows = ft_atoi(line + 6);
	while (line[i] != ' ')
		i++;
	i++;
	run->p_col = ft_atoi(line + i);
	ft_strdel(&line);
    i = 0;
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
