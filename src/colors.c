/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:09:02 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/02 16:39:20 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	put_color(void)
{
	int		i;
	char	*line;

	while (get_next_line(0, &line) && ft_strstr(line, "Piece") == 0)
	{
		i = 4;
		while (line[i])
		{
			if (line[i] == 'X')
				ft_printf("{red}%c{reset}", line[i]);
			else if (line[i] == 'O')
				ft_printf("{green}%c{reset}", line[i]);
			else if (line[i] == 'o' || line[i] == 'x')
				ft_printf("{magenta}%c{reset}", line[i]);
			else
				ft_printf("%c", line[i]);
			i++;
		}
		ft_printf("\n");
		ft_strdel(&line);
	}
	if (ft_strstr(line, "Piece") != 0)
		ft_printf("%s\n", line);
}

void	who_won(int o, int x)
{
	ft_printf("\n");
	if (x > o)
		ft_printf("{magenta}%s{reset}\n", "Player 2 won!");
	else if (x < o)
		ft_printf("{magenta}%s{reset}\n", "Player 1 won!");
	else if (x == 0)
		ft_printf("{magenta}%s{reset}\n", "Draw!");
}

int		main(void)
{
	char	*ln;
	int		x;
	int		o;

	get_next_line(0, &ln);
	ft_strdel(&ln);
	while (get_next_line(0, &ln))
	{
		if (ft_strstr(ln, "   ") != 0)
			put_color();
		else
		{
			if (ft_strstr(ln, "== O") != 0)
				ft_printf("{green}%s{reset}\n", ln) && (o = ft_atoi(ln + 9));
			else if (ft_strstr(ln, "== X") != 0)
				ft_printf("{red}%s{reset}\n", ln) && (x = ft_atoi(ln + 9));
			else
				printf("%s\n", ln);
		}
	}
	who_won(o, x);
	return (1);
}
