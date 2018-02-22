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
	int			connect;
    char        **field;
    char        **piece;
}				t_lst;

int		logic(char **field, char **piece, t_lst *run);
void	print(char **res);

#endif