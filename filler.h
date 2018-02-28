/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:01:38 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/02/15 12:01:39 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "./libft/libft.h"
# include "./GNL/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_lst
{
	int			rows;
	int			columns;
	int			p_rows;
	int			p_col;
	char		me;
	char		an;
	int 		best_x;
	int 		best_y;
    char        **field;
    char        **piece;
	int         dist;
	int         i_en;
	int         j_en;
}				t_lst;

void	print(char **res);
char	**get_field(int fd, t_lst *run, char *line);
char	**get_piece(int fd, t_lst *run);
void    ft_free(char **array);
void	ft_filler(t_lst *run);
int		get_player(int fd);

#endif