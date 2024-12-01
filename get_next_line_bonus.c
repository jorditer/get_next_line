/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordi <jordi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:30:35 by jterrada          #+#    #+#             */
/*   Updated: 2024/12/01 23:10:21 by jordi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define MAX_FD 1024

static char	*read_and_store(int fd, char *chunk)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(chunk), NULL);
		buffer[bytes_read] = '\0';
		if (!chunk)
			chunk = ft_strdup("");
		tmp = chunk;
		chunk = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!chunk || ft_strchr(chunk, '\n'))
			break ;
	}
	if (!chunk || !tmp)
		return (NULL);
	return (free(buffer), chunk);
}

static char	*extract_line(char **chunk)
{
	char	*newline_pos;
	char	*line;
	char	*tmp;

	newline_pos = ft_strchr(*chunk, '\n');
	if (newline_pos)
	{
		line = ft_substr(*chunk, 0, newline_pos - *chunk + 1);
		tmp = *chunk;
		*chunk = ft_strdup(newline_pos + 1);
		free(tmp);
	}
	else
	{
		line = ft_strdup(*chunk);
		free(*chunk);
		*chunk = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*chunks[MAX_FD];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	chunks[fd] = read_and_store(fd, chunks[fd]);
	if (!chunks[fd] || chunks[fd][0] == '\0')
	{
		free(chunks[fd]);
		chunks[fd] = NULL;
		return (NULL);
	}
	line = extract_line(&chunks[fd]);
	return (line);
}

// void	ft_putstr(char *s)
// {
// 	while (*s)
// 	{
// 		write(1, s, 1);
// 		s++;
// 	}
// }
// int main() {
//     int fd = open("test.txt", O_RDONLY);
//     int fd2 = open("test2.txt", O_RDONLY);
//     char *result;

//     if (fd < 0 || fd2 < 0) {
//         perror("Error opening file");
//         return 1;
//     }

//     while (1) {
//         // fd 1
//         result = get_next_line(fd);
//         if (!result)
//             break;
//         ft_putstr(result);
//         free(result);

//         // fd 2
//         result = get_next_line(fd2);
//         if (!result)
//             break;
//         ft_putstr(result);
//         free(result);
//     }
//     result = get_next_line(fd);
//     if (!result) {
//         ft_putstr("\nNULL 1\n");
//         return 1;
//     }
//     ft_putstr(result);
//     free(result);

//     result = get_next_line(fd2);
//     if (!result) {
//         ft_putstr("\nNULL 2\n");
//         return 2;
//     }
//     if (close(fd) == -1 || close(fd2) == -1) {
//         write(2, "Cannot close file.\n", 19);
//         return 1;
//     }

//     return 0;
// }