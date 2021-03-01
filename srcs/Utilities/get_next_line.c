/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:44:34 by adel-sol          #+#    #+#             */
/*   Updated: 2021/01/05 10:26:54 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		fill_line(char **line, char **save, int indx, int ret)
{
	char	*new_save;

	if (ret == 0)
		indx = my_strchr(*save, '\n', ret);
	if (indx == -2)
	{
		if (!(*line = ft_strdup(*save)))
			return (-1);
		if (save && *save)
		{
			free(*save);
			*save = NULL;
			return (0);
		}
	}
	else
	{
		if (!(*line = ft_substr(*save, 0, indx)) ||
			!(new_save = ft_strdup(&(*save)[indx + 1])))
			return (-1);
		free(*save);
		*save = new_save;
	}
	return (1);
}

int		get_ret_val(char **line, char **save, int indx, int ret)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && *save == NULL)
	{
		*line = malloc(1);
		**line = 0;
		return (0);
	}
	return (fill_line(line, save, indx, ret));
}

int		read_buff(char *buff, int fd, char **save, int *indx)
{
	int		ret;
	char	*new_save;

	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (*save == NULL)
		{
			if (!(*save = ft_strdup(buff)))
				return (-1);
		}
		else
		{
			if (!(new_save = ft_strjoin(*save, buff)))
				return (-1);
			free(*save);
			*save = new_save;
		}
		if ((*indx = my_strchr(*save, '\n', ret)) != -1)
			break ;
	}
	free(buff);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*save;
	int				ret;
	int				indx;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if ((ret = read_buff(buff, fd, &save, &indx)) == -1)
		return (-1);
	return (get_ret_val(line, &save, indx, ret));
}
