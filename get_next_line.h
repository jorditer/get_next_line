#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

size_t	ft_strcpy(char *dest, const char *src);
int		ft_strlen(char *str);
char	*ft_strdup(const char *src);
char	*ft_substr(char *s, int start, int len);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char*dest, const char *src, size_t size);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
