/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:28:59 by jterrada          #+#    #+#             */
/*   Updated: 2024/09/24 23:13:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
// #include "get_next_line_utils.c"

#define BUFF_SIZE 42 

// el arg int n no tiene sentido, solo es para las 25 lineas
char	*fill_line(int fd, char *buff)
{
	char	*line;
	char	*temp;
	int		n;

	n = 0;
	line = ft_strdup("");
	while (1)
	{
		n = read(fd, buff, BUFF_SIZE);
		if (n == -1 || (n == 0 && ft_strlen(line) == 0))
		{
			free(line);
			return (NULL);
		}
		if (n == 0)
			break ;
		buff[n] = '\0';
		temp = line;
		line = ft_strjoin(temp, buff);
		free(temp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (line);
}

char	*split_line(char *str)
{
	char	*rest;
	int		null_position;
	char	*temp;

	null_position = 0;
	temp = ft_strchr(str, '\n');
	if (temp)
	{
		null_position = temp - str;
		rest = ft_strdup(temp + 1);
		str[null_position + 1] = '\0';
	}
	else
		rest = NULL;
	return (rest);
}

char	*get_next_line(int fd)
{
	static char		*rest;
	char			*line;
	char			*buff;
	char			*temp;

	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buff)
		return (NULL);
	line = fill_line(fd, buff);
	free(buff);
	if (!line)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	if (rest)
	{
		temp = ft_strjoin(rest, line);
		free(line);
		free(rest);
		line = ft_strdup(temp);
		free(temp);
	}
	rest = split_line(line);
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
	result = get_next_line(fd);
	ft_putstr(result);
	result = get_next_line(fd);
	ft_putstr(result);
	// while (1)
	// {
	// 	result = get_next_line(fd);
	// 	if  (!result)
	// 		break ;
	// 	ft_putstr(result);
	// 	free(result);
	// }
	if (close(fd) == -1)
	{
		write(2, "Cannot close file.\n", 19);
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	char *rest;

// 	rest = ft_strdup("test1\ntest2");
// 	ft_putstr(split_line(rest));
// 	ft_putstr(rest);
// }