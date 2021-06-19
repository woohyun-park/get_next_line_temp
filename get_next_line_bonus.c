/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woopark <woopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:24:07 by woopark           #+#    #+#             */
/*   Updated: 2021/06/19 18:19:30 by woopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	index_of(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	assign_line(char **from, char **to, int size)
{
	char	*temp;

	if (!(*to = malloc(size + 1)))
		return (-1);
	ft_strlcpy(*to, *from, size + 1);
	temp = ft_strdup(*from + size + 1);
	free(*from);
	*from = temp;
	return (1);
}

int	assign_line_last(char **from, char **to, int size)
{
	if (!(*to = malloc(size + 1)))
		return (-1);
	ft_strlcpy(*to, *from, size + 1);
	free(*from);
	*from = NULL;
	return (0);
}

int	read_and_assign_line(int fd, char **line, char *buf, char **save)
{
	char	*temp;
	int		index;
	int		size_read;

	while ((size_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		(buf)[size_read] = 0;
		temp = *save ? ft_strjoin(*save, buf) : ft_strdup(buf);
		free(*save);
		*save = temp;
		if ((index = index_of(*save, '\n')) >= 0)
		{
			free(buf);
			return (assign_line(save, line, index));
		}
	}
	free(buf);
	if (size_read < 0)
	{
		free(*save);
		return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*save[OPEN_MAX];
	char		*buf;
	int			index;
	int			result;

	if (fd < 0 || fd > OPEN_MAX || line == 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!save[fd])
		save[fd] = ft_strdup("");
	if ((result = read_and_assign_line(fd, line, buf, &save[fd])) != 0)
		;
	else if ((index = index_of(save[fd], '\n')) >= 0)
		result = assign_line(&save[fd], line, index);
	else
		result = assign_line_last(&save[fd], line, ft_strlen(save[fd]));
	return (result);
}
