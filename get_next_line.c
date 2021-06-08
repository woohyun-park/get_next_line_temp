#include "get_next_line.h"

int index_of(char *str, char c)
{
	int	i;
	
	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	assign_line(char **from, char **to, int size)
{
	
	if(!(*to = malloc(size + 1)))
		return (-1);
	ft_strlcpy(*to, *from, size + 1);
	*from = size == BUFFER_SIZE ? *from + size : *from + size + 1;
	return (1);
}

int	assign_line_last(char **from, char **to, int size)
{
	if(size <= 0 && ft_strlen(*from) <= BUFFER_SIZE){
		ft_strlcpy(*to, *from, ft_strlen(*from) + 1);
		return (0);
	}
	if(!(*to = malloc(size + 1)))
		return (-1);
	ft_strlcpy(*to, *from, size + 1);
	*from = size == BUFFER_SIZE ? *from + size : *from + size + 1;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*buf_save[OPEN_MAX];
	char		*buf;
	int			index;
	int			size_read;
	
	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((size_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[size_read] = 0;
		buf_save[fd] = ft_strjoin(buf_save[fd], buf);
		if((index = index_of(buf_save[fd], '\n')) != -1)
			return (assign_line(&buf_save[fd], line, index));
	}
	return assign_line_last(&buf_save[fd], line, ft_strlen(buf_save[fd]));
}

int	main(void)
{
	int		temp;
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while ((temp = (get_next_line(fd, &line)) > 0))
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
	close(fd);
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return (0);
}