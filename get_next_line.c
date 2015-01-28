/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refonte.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroignan <rroignan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:00:52 by rroignan          #+#    #+#             */
/*   Updated: 2015/01/28 19:23:13 by rroignan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	char		*buf;
	char		*temp;
	static char	*stockage;
	int			ret;

	buf = ft_strnew(BUF_SIZE);
	temp = ft_strnew(1);
	if (fd < 0 || BUF_SIZE < 0 || line == NULL)
		return (-1);
	if (!*line)
		*line = ft_strnew(1);
	if (stockage != NULL)
	{
		temp = ft_strjoin(temp, stockage);
		ft_strclr(stockage);
	}
	if (temp != NULL && ft_strchr(temp, '\n') != NULL)
	{
		*line = ft_strsub(temp, 0, (ft_strchr(temp, '\n') - temp));
		stockage = ft_strsub(temp, (ft_strchr(temp, '\n') - temp) + 1, ft_strchr(temp, '\0') - ft_strchr(temp, '\n'));
		ft_strdel(&temp);
		ft_strdel(&buf);
		return (1);
	}
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
	{
		temp = ft_strjoin(temp, buf);
		ft_strclr(buf);
		if (ft_strchr(temp, '\n') != NULL)
			break ;
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && (stockage == NULL || stockage[0] == '\0') && temp[0] == '\0')
		return (0);
	if (ft_strchr(temp, '\n') == NULL && ret == 0)
	{
		*line = ft_strsub(temp, 0, ft_strchr(temp, '\0') - temp);
		ft_strdel(&temp);
		ft_strdel(&stockage);
		return (1);
	}
	*line = ft_strsub(temp, 0, (ft_strchr(temp, '\n') - temp));
	stockage = ft_strsub(temp, (ft_strchr(temp, '\n') - temp) + 1, ft_strchr(temp, '\0') - ft_strchr(temp, '\n'));
	ft_strdel(&temp);
	ft_strdel(&buf);
	return (1);
}
