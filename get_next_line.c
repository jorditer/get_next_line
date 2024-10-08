/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:28:59 by jterrada          #+#    #+#             */
/*   Updated: 2024/10/08 22:37:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line(char *buff, int fd, char *chunk)
{
	ssize_t	n;
	char	*tmp;

	while (1)
	{
		n = read(fd, buff, BUFF_SIZE);
		if (n == -1)
		{
			free(chunk);
			return (NULL);
		}
		if (n == 0)
			break ;
		buff[n] = '\0';
		if (!chunk)
			chunk = ft_strdup("");
		tmp = chunk;
		chunk = ft_strjoin(tmp, buff);
		free(tmp);
		if (!chunk)
			return (NULL);
		if (ft_strchr(chunk, '\n'))
			break ;
	}
	return (chunk);
}

char	*handle_line(char **chunk)
{
	char	*newline_pos;
	char	*line;
	char	*left;

	newline_pos = ft_strchr(*chunk, '\n');
	if (newline_pos)
	{
		line = ft_substr(*chunk, 0, newline_pos - *chunk + 1);
		left = ft_strdup(newline_pos + 1);
		free(*chunk);
		*chunk = left;
		return (line);
	}
	line = ft_strdup(*chunk);
	free(*chunk);
	*chunk = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*chunk;
	char		*line;

	buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buff)
		return (NULL);
	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buff, 0) < 0)
	{
		free(buff);
		return (NULL);
	}
	chunk = fill_line(buff, fd, chunk);
	free(buff);
	if (!chunk)
		return (NULL);
	line = handle_line(&chunk);
	return (line);
}

void	ft_putstr(char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}
int	main(void)
{
	int		fd;
	char	*result;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	// result = get_next_line(fd);
	// ft_putstr(result);
	// free(result);
	while (1)
	{
		result = get_next_line(fd);
		if  (!result)
			break ;
		ft_putstr(result);
		free(result);
	}
	// result = get_next_line(fd);
	// ft_putstr(result);
	// free(result);
	if (close(fd) == -1)
	{
		write(2, "Cannot close file.\n", 19);
		return (1);
	}
	return (0);
}