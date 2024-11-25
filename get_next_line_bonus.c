#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_FD 1024

char *get_next_line(int fd) {
    static char *chunks[MAX_FD];
    char buffer[BUFFER_SIZE + 1];
    char *line = NULL;
    char *tmp;
    ssize_t bytes_read;
    char *newline_pos;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0) {
        return NULL;
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';
        if (!chunks[fd]) {
            chunks[fd] = strdup("");
        }
        tmp = chunks[fd];
        chunks[fd] = strjoin(tmp, buffer);
        free(tmp);
        if ((newline_pos = strchr(chunks[fd], '\n'))) {
            *newline_pos = '\0';
            line = strdup(chunks[fd]);
            tmp = chunks[fd];
            chunks[fd] = strdup(newline_pos + 1);
            free(tmp);
            return line;
        }
    }

    if (bytes_read < 0 || (!chunks[fd] && bytes_read == 0)) {
        return NULL;
    }

    if (chunks[fd] && *chunks[fd] != '\0') {
        line = strdup(chunks[fd]);
        free(chunks[fd]);
        chunks[fd] = NULL;
        return line;
    }

    free(chunks[fd]);
    chunks[fd] = NULL;
    return NULL;
}

void ft_putstr(char *s) {
    while (*s) {
        write(1, s, 1);
        s++;
    }
}

int main() {
    int fd = open("test.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    char *result;

    if (fd < 0 || fd2 < 0) {
        perror("Error opening file");
        return 1;
    }

    while (1) {
        // fd 1
        result = get_next_line(fd);
        if (!result)
            break;
        ft_putstr(result);
        free(result);

        // fd 2
        result = get_next_line(fd2);
        if (!result)
            break;
        ft_putstr(result);
        free(result);
    }

    if (close(fd) == -1 || close(fd2) == -1) {
        write(2, "Cannot close file.\n", 19);
        return 1;
    }

    return 0;
}