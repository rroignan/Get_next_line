/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refonte.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroignan <rroignan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:00:52 by rroignan          #+#    #+#             */
/*   Updated: 2015/01/28 20:47:34 by rroignan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_fill(char ***str, char **stk, char **tmp, char **fub)
{
	**str = ft_strsub(*tmp, 0, (ft_strchr(*tmp, '\n') - *tmp));
	*stk = ft_strsub(*tmp, (ft_strchr(*tmp, '\n') - *tmp) + 1, ft_strchr(*tmp, '\0') - ft_strchr(*tmp, '\n'));
	ft_strdel(tmp);
	ft_strdel(fub);
}

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
		ft_fill(&line, &stockage, &temp, &buf);
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
	ft_fill(&line, &stockage, &temp, &buf);
	return (1);
}
