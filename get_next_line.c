/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woopark <woopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:24:07 by woopark           #+#    #+#             */
/*   Updated: 2021/09/11 21:25:11 by woopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

char	*assign_line(char **from, int size)
{
	char	*temp;
	char	*result;

	// printf("from: %s,size: %d\n", *from, size);
	result = malloc(size + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, *from, size + 2);
	temp = ft_strdup(*from + size + 1);
	free(*from);
	*from = temp;
	return (result);
}

char	*assign_line_last(char **from, int size)
{
	char	*result;
	
	result = malloc(size + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, *from, size + 1);
	free(*from);
	*from = NULL;
	return (result);
}

// int	read_and_assign_line(int fd, char *buf, char **save)
// {
// 	char	*temp;
// 	int		index;
// 	int		size_read;

// 	while ((size_read = read(fd, buf, BUFFER_SIZE)) > 0)
// 	{
// 		(buf)[size_read] = 0;
// 		temp = *save ? ft_strjoin(*save, buf) : ft_strdup(buf);
// 		free(*save);
// 		*save = temp;
// 		if ((index = index_of(*save, '\n')) >= 0)
// 		{
// 			free(buf);
// 			return (assign_line(save, index));
// 		}
// 	}
// 	free(buf);
// 	if (size_read < 0)
// 	{
// 		free(*save);
// 		return (0);
// 	}
// 	return (0);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*save[OPEN_MAX];
// 	char		*buf;
// 	int			index;
// 	int			result;

// 	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
// 		return (-1);
// 	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buf)
// 		return (-1);
// 	if (!save[fd])
// 		save[fd] = ft_strdup("");
// 	result = read_and_assign_line(fd, line, buf, &save[fd]);
// 	index = index = index_of(save[fd], '\n');
// 	if (result != 0)
// 		return (result);
// 	if (index >= 0)
// 		return = assign_line(&save[fd], index);
// 	return = assign_line_last(&save[fd], ft_strlen(save[fd]));
// }

int	read_and_assign_line(int fd, char *buf, char **save, char **result)
{
	char	*temp;
	int		index;
	int		size_read;

	size_read = read(fd, buf, BUFFER_SIZE);
	if(size_read == 0)
		return (-1);
	while (size_read > 0)
	{
		(buf)[size_read] = 0;
		temp = *save ? ft_strjoin(*save, buf) : ft_strdup(buf);
		free(*save);
		*save = temp;
		index = index_of(*save, '\n');
		if (index >= 0)
		{
			free(buf);
			*result = assign_line(save, index);
			return (0);
		}
		size_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (size_read < 0)
	{
		// printf("here\n");
		if(!*save)
			free(*save);
		*result = NULL;
		return (-1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char *save[OPEN_MAX];
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
	if(status == -1)
		return NULL;
	if(status == 1)
	{
		index = index_of(save[fd], '\n');
		if (index >= 0)
			result = assign_line(&save[fd], index);
		else
			result = assign_line_last(&save[fd], ft_strlen(save[fd]));
	}
	return (result);
}


// #include <fcntl.h>
// #include <stdio.h>
// int main(void){
// 	int fd = open("./text.txt", O_RDWR);
// 	char	*temp;

// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// }

// #include <stdio.h>
// #include <fcntl.h>
// int main(void){
// 	int file = open("text.txt", O_RDWR);
// 	printf("-%s-", get_next_line(file));
// }