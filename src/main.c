/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:39:56 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/02 16:40:58 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_link	*new_list(void)
{
	t_link	*run;

	run = (t_link*)malloc(sizeof(t_link));
	run->an = 0;
	run->me = 0;
	run->best_x = 0;
	run->best_y = 0;
	run->columns = 0;
	run->rows = 0;
	run->p_col = 0;
	run->p_rows = 0;
	run->field = NULL;
	run->piece = NULL;
	run->dist = 0;
	run->i_en = 0;
	run->j_en = 0;
	run->connect = 0;
	run->stars = 0;
	run->stars_count = 0;
	return (run);
}

int		main(void)
{
	t_link	*run;

	run = new_list();
	ft_filler(run);
	return (1);
}
