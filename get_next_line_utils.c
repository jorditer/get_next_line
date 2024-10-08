/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:04:10 by jterrada          #+#    #+#             */
/*   Updated: 2024/10/08 20:25:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}



// size_t	ft_strlcat(char *dest, const char *src, size_t size)
// {
// 	size_t	src_len;
// 	size_t	dest_len;
// 	int		i;

// 	if ((dest == NULL || src == NULL) && size <= 0)
// 		return ((size_t) - 1);
// 	src_len = 0;
// 	dest_len = 0;
// 	while (dest[dest_len] && dest_len < size)
// 		dest_len++;
// 	while (src[src_len])
// 		src_len++;
// 	if (size <= dest_len)
// 		return (dest_len + src_len);
// 	i = 0;
// 	while (src[i] && (dest_len + i) < (size - 1))
// 	{
// 		dest[dest_len + i] = src[i];
// 		i++;
// 	}
// 	dest[dest_len + i] = '\0';
// 	return (dest_len + src_len);
// }

char	*ft_substr(char *s, int start, int len)
{
	int	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	d;

	d = (unsigned char)c;
	if (d == '\0')
		return ((char *)s);
	while (*s)
	{
		if (*s == d)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	dest = (char *)malloc(i + 1);
	if (dest == NULL)
		return (NULL);
	while (i >= 0)
	{
		dest[i] = src[i];
		i--;
	}
	return (dest);
}

// size_t	ft_strcpy(char *dest, const char *src)
// {
// 	size_t	i;
// 	size_t	len;

// 	len = 0;
// 	while (src[len])
// 		len++;
// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (len);
// }

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;

	i = 0;
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	while (*s1)
		s3[i++] = *s1++;
	while (*s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	return (s3);
}