/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroignan <rroignan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 11:52:16 by rroignan          #+#    #+#             */
/*   Updated: 2015/01/28 11:40:01 by rroignan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		main()
{
	int		fd;
	char	*line;

	fd = open("sns", O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		ft_putendl(line);
	/*get_next_line(fd, &line);
	ft_putendl(line);
	get_next_line(fd, &line);
	ft_putendl(line);
	get_next_line(fd, &line);
	ft_putendl(line);
	get_next_line(fd, &line);
	ft_putendl(line);
	get_next_line(fd, &line);
	ft_putendl(line);
	get_next_line(fd, &line);
	ft_putendl(line);*/
	return (0);
}
