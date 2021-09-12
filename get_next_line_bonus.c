/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woopark <woopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:24:07 by woopark           #+#    #+#             */
/*   Updated: 2021/09/12 21:50:46 by woopark          ###   ########.fr       */
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

char	*assign_line(char **from, int size, int is_last)
{
	char	*temp;
	char	*result;

	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (0);
	if (!is_last)
	{
		ft_strlcpy(result, *from, size + 2);
		temp = ft_strdup(*from + size + 1);
		free(*from);
		*from = temp;
		return (result);
	}
	ft_strlcpy(result, *from, size + 1);
	free(*from);
	*from = NULL;
	return (result);
}

int	read_line(char *buf, char **save, char **result, int size_read)
{
	char	*temp;
	int		index;

	(buf)[size_read] = 0;
	if (*save)
		temp = ft_strjoin(*save, buf);
	else
		temp = ft_strdup(buf);
	free(*save);
	*save = temp;
	index = index_of(*save, '\n');
	if (index >= 0)
	{
		free(buf);
		*result = assign_line(save, index, 0);
		return (0);
	}
	return (1);
}

int	read_and_assign_line(int fd, char *buf, char **save, char **result)
{
	int		size_read;

	size_read = read(fd, buf, BUFFER_SIZE);
	if (size_read <= 0 && ft_strlen(*save) == 0)
	{
		free(buf);
		free(*save);
		*save = NULL;
		return (-1);
	}
	while (size_read > 0)
	{
		if (!read_line(buf, save, result, size_read))
			return (0);
		size_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (size_read < 0)
	{
		free(*save);
		*save = NULL;
		return (-1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*buf;
	int			index;
	int			status;
	char		*result;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	if (!save[fd])
		save[fd] = ft_strdup("");
	status = read_and_assign_line(fd, buf, &save[fd], &result);
	if (status == -1)
		return (NULL);
	if (status == 1)
	{
		index = index_of(save[fd], '\n');
		if (index >= 0)
			result = assign_line(&save[fd], index, 0);
		else
			result = assign_line(&save[fd], ft_strlen(save[fd]), 1);
	}
	return (result);
}