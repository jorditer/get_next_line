#include "get_next_line_bonus.h"

#define MAX_FD 1024

static char	*read_and_store(int fd, char *chunk)
{
    char	*buffer;
    char	*tmp;
    ssize_t	bytes_read;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return NULL;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        if (!chunk)
            chunk = ft_strdup("");
        tmp = chunk;
        chunk = ft_strjoin(tmp, buffer);
        free(tmp);
        if (ft_strchr(chunk, '\n'))
            break;
    }
    free(buffer);
    return chunk;
}

static char	*extract_line(char **chunk)
{
    char	*newline_pos;
    char	*line;
    size_t	line_length;
    size_t	remaining_length;

    newline_pos = ft_strchr(*chunk, '\n');
    if (newline_pos)
    {
        line_length = newline_pos - *chunk + 1;
        remaining_length = ft_strlen(newline_pos + 1);
        line = malloc(line_length + 1);
        if (!line)
            return NULL;
        ft_strncpy(line, *chunk, line_length);
        line[line_length] = '\0';
        ft_memmove(*chunk, newline_pos + 1, remaining_length + 1);
    }
    else
    {
        line = ft_strdup(*chunk);
        free(*chunk);
        *chunk = NULL;
    }
    return line;
}

char	*get_next_line(int fd)
{
    static char	*chunks[MAX_FD];
    char		*line;

    line = NULL;
    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return NULL;
    chunks[fd] = read_and_store(fd, chunks[fd]);
    if (!chunks[fd] || chunks[fd][0] == '\0')
    {
        free(chunks[fd]);
        chunks[fd] = NULL;
        return NULL;
    }
    line = extract_line(&chunks[fd]);
    return line;
}

// void	ft_putstr(char *s)
// {
// 	while (*s)
// 	{
// 		write(1, s, 1);
// 		s++;
// 	}
// }

// int	main()
// {
// 	int		fd;
// 	char	*result;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return 1;
// 	}

// 	while ((result = get_next_line(fd)) != NULL)
// 	{
// 		ft_putstr(result);
// 		free(result);
// 	}

// 	if (close(fd) == -1)
// 	{
// 		write(2, "Cannot close file.\n", 19);
// 		return 1;
// 	}

// 	return 0;
// }