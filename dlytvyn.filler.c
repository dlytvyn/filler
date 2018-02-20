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

int		get_player(int fd)
{
	char	*line;
	int		res;

	res = 0;
	line = NULL;
	get_next_line(fd, &line);
	if (ft_strstr(line, "dlytvyn.filler") != 0)
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

void	ft_filler(t_lst *run)
{
	int		fd;
	char	*line;
	int		i;
	char	**field;
	char	**piece;

	fd = open("/Users/dlytvyn/Filler/map00", O_RDONLY);
	fd = 0;
	if (fd < 0)
		exit(0);
	i = 0;
	run->me = (get_player(fd) == 1) ? 'O' : 'X';
	run->an = (run->me == 'O') ? 'X' : 'O';
	while (get_next_line(fd, &line) && ft_strstr(line, "Plateau") == 0)
	i = 0;
	while (line[i] < '1' || line[i] > '9')
		i++;
	run->rows = ft_atoi(line + i);
	while (line[i] != ' ')
		i++;
	i++;
	run->columns = ft_atoi(line + i);
	ft_strdel(&line);
	while (get_next_line(fd, &line))
	{
		if (ft_strstr(line, "Plateau") != 0)
		{
			ft_strdel(&line);
			get_next_line(fd, &line);
		}
		//get_next_line(fd, &line);
		field = get_field(fd, run);
		get_next_line(fd, &line);
		i = 0;
		while (line[i] < '1' || line[i] > '9')
			i++;
		run->p_rows = ft_atoi(line + i);
		while (line[i] != ' ')
			i++;
		i++;
		run->p_col = ft_atoi(line + i);
		piece = get_piece(fd, run);
		logic(field, piece, run);
		run->best_x = -1;
		run->best_y = -1;
		run->connect = -1;
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
	return (run);
}

int	main()
{
	t_lst *run;

	run = new_list();
	ft_filler(run);
	return (1);
}
