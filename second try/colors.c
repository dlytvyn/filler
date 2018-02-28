/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:09:02 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/02/28 18:09:03 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int main()
{
    int fd;
    int i;
    char *line;

    fd = 0;
    get_next_line(fd, &line);
    ft_strdel(&line);
    while (get_next_line(fd, &line))
    {
        if (ft_strstr(line, "   ") != 0)
        {
            while (get_next_line(fd, &line) && ft_strstr(line, "Piece") == 0)
            {
                i = 4;
                while (line[i])
                {
                    if (line[i] == 'X')
                        ft_printf("{red}%c{reset}", line[i]);
                    else if (line[i] == 'O')
                        ft_printf("{green}%c{reset}", line[i]);
                    else if (line[i] == 'o' || line[i] == 'x')
                        ft_printf("{blue}%c{reset}", line[i]);
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
        else
        {
            if (ft_strstr(line, "== O") != 0)
                ft_printf("{green}%s{reset}\n", line);
            else if (ft_strstr(line, "== X") != 0)
                ft_printf("{red}%s{reset}\n", line);
            else
                printf("%s\n", line);
        }
    }
    return (1);
}


/*
int main()
{
    ft_printf("{blue}%s{reset} %s\n", "hello", "world!");
    return (1);
}
*/