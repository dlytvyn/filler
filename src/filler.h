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

# include "../libft/libft.h"
# include "../GNL/get_next_line.h"
# include "../ft_printf/ft_printf/print.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define ARR1 run->piece[i2 + i_plus][j2 + j_plus] == '*'
# define ARR2 run->field[i][j] == run->me || run->field[i][j] == run->me + 32
# define ARR3 run->piece[i2 + i_plus][j2 + j_plus] == '*'
# define ARR4 run->field[i][j] == run->an || run->field[i][j] == run->an + 32
# define ARR5 run->field[i][j] && run->piece[i2 + i_plus][j2 + j_plus]
# define ARR6 run->piece[i2 + i_plus][j2 + j_plus]

typedef struct	s_link
{
	int			rows;
	int			columns;
	int			p_rows;
	int			p_col;
	char		me;
	char		an;
	int			best_x;
	int			best_y;
	char		**field;
	char		**piece;
	int			dist;
	int			i_en;
	int			j_en;
	int			connect;
	int			stars;
	int			stars_count;
}				t_link;

char			**get_field(int fd, t_link *run, char *line);
char			**get_piece(int fd, t_link *run);
void			ft_free(char **array);
void			ft_filler(t_link *run);
int				get_player(int fd);
void			search_enemy_down(char **field, t_link *run, int i2, int j2);
void			search_enemy_up(char **field, t_link *run, int i2, int j2);
int				module(int a);
int				plus_i(char **piece);
int				plus_j(char **piece);
int				st(char *line);
int				count_stars(char **piece);
int				ft_try_put(int i, int j, t_link *run);

#endif
