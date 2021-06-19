/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woopark <woopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:24:07 by woopark           #+#    #+#             */
/*   Updated: 2021/06/19 13:18:58 by woopark          ###   ########.fr       */
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

	if (size == 0)
	{
		*to = ft_strdup("");
		temp = ft_strdup(*from + 1);
		if (**from)
			free(*from);
		*from = temp;
		return (1);
	}
	if (!(*to = malloc(size + 1)))
		return (-1);
	ft_strlcpy(*to, *from, size + 1);
	temp = ft_strdup(*from + size + 1);
	if (**from)
		free(*from);
	*from = temp;
	return (1);
}

int	assign_line_last(char **from, char **to, int size)
{
	if (size == 0)
	{
		*to = ft_strdup("");
		free(*from);
		*from = NULL;
		return (0);
	}
	if (!(*to = malloc(size + 1)))
		return (-1);
	ft_strlcpy(*to, *from, size + 1);
	free(*from);
	*from = NULL;
	return (0);
}

int	asdf(char **buf, int size_read, char **buf_save, char **line)
{
	char	*temp;
	int		index;

	(*buf)[size_read] = 0;
	if (buf_save)
		temp = ft_strjoin(*buf_save, *buf);
	else
		temp = ft_strdup(*buf);
	if (*buf_save)
		free(*buf_save);
	*buf_save = temp;
	if ((index = index_of(*buf_save, '\n')) >= 0)
	{
		free(*buf);
		return (assign_line(buf_save, line, index));
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*buf_save[OPEN_MAX];
	char		*buf;
	int			index;
	int			size_read;

	if (fd < 0 || fd > OPEN_MAX || line == 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!buf_save[fd])
		buf_save[fd] = ft_strdup("");
	while ((size_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (asdf(&buf, size_read, &(buf_save[fd]), line) == 1)
			return (1);
	}
	free(buf);
	if (size_read < 0)
	{
		free(buf_save[fd]);
		return (-1);
	}
	if ((index = index_of(buf_save[fd], '\n')) >= 0)
		return (assign_line(&buf_save[fd], line, index));
	return (assign_line_last(&buf_save[fd], line, ft_strlen(buf_save[fd])));
}
