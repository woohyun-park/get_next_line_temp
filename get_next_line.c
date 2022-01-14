/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woopark <woopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:24:07 by woopark           #+#    #+#             */
/*   Updated: 2022/01/14 14:42:45 by woopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*create_next_line(char **save, int index)
{
	char	*result;
	char	*tmp_result;
	char	*tmp;

	(*save)[index] = 0;
	result = ft_strdup(*save);
	tmp_result = ft_strjoin(result, "\n");
	free(result);
	result = tmp_result;
	if (*(*save + index + 1) == '\0')
		tmp = 0;
	else
		tmp = ft_strdup((*save) + index + 1);
	free(*save);
	*save = tmp;
	return (result);
}

char	*create_last_line(char **save, int size)
{
	int		index;
	char	*result;

	if (size < 0)
		return (0);
	if (!*save)
		return (0);
	index = is_line(*save);
	if (index < 0)
	{
		result = *save;
		*save = 0;
		return (result);
	}
	return (create_next_line(save, index));
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	int			index;
	int			size_read;
	char		*tmp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	size_read = read(fd, buf, BUFFER_SIZE);
	while (size_read > 0)
	{
		buf[size_read] = 0;
		tmp = ft_strjoin(save[fd], buf);
		free(save[fd]);
		save[fd] = tmp;
		index = is_line(save[fd]);
		if (index >= 0)
			return (create_next_line(&save[fd], index));
		size_read = read(fd, buf, BUFFER_SIZE);
	}
	return (create_last_line(&save[fd], size_read));
}
