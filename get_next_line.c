/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refonte.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroignan <rroignan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:00:52 by rroignan          #+#    #+#             */
/*   Updated: 2015/02/02 11:08:39 by rroignan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_loop(char **tmp, char **fub)
{
	*tmp = ft_strjoin(*tmp, *fub);
	ft_strclr(*fub);
}

static void		ft_alou(char **str, char **stn)
{
	*str = ft_strnew(BUF_SIZE);
	*stn = ft_strnew(1);
}

static int		ft_fill(char ***str, char **stk, char **tmp, char **fub)
{
	char		*chr;

	chr = ft_strchr(*tmp, '\n');
	ft_strclr(*stk);
	**str = ft_strsub(*tmp, 0, (chr - *tmp));
	*stk = ft_strsub(*tmp, (chr - *tmp) + 1, ft_strchr(*tmp, '\0') - chr);
	ft_strdel(tmp);
	ft_strdel(fub);
	return (1);
}

static int		ft_lastline(char ***str, char **tmp, char **stk)
{
	**str = ft_strsub(*tmp, 0, ft_strchr(*tmp, '\0') - *tmp);
	ft_strdel(tmp);
	ft_strdel(stk);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char		*buf;
	char		*temp;
	static char	*sto;
	int			ret;

	if (line == NULL)
		return (-1);
	ft_alou(&buf, &temp);
	(!*line ? *line = ft_strnew(1) : *line);
	((sto != NULL) ? temp = ft_strjoin(temp, sto) : temp);
	if (temp != NULL && ft_strchr(temp, '\n') != NULL)
		return (ft_fill(&line, &sto, &temp, &buf));
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
	{
		ft_loop(&temp, &buf);
		if (ft_strchr(temp, '\n') != NULL)
			break ;
	}
	if (fd < 0 || BUF_SIZE < 0 || ret == -1)
		return (-1);
	if (ret == 0 && (sto == NULL || sto[0] == '\0') && temp[0] == '\0')
		return (0);
	if (ft_strchr(temp, '\n') == NULL && ret == 0)
		return (ft_lastline(&line, &temp, &sto));
	return (ft_fill(&line, &sto, &temp, &buf));
}
