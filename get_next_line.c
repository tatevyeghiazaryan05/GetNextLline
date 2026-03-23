/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyeghiaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 19:42:42 by tyeghiaz          #+#    #+#             */
/*   Updated: 2026/03/23 20:02:27 by tyeghiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	string_len;
	char	*sub;

	if (!s)
		return (NULL);
	string_len = ft_strlen(s);
	if (start >= string_len)
	{
		sub = (char *)malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len + start > string_len)
		len = string_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

char	*ft_read_and_fill_reminder(int fd, char *reminder)
{
	int		read_bytes;
	char	*buffer;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(reminder, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		tmp = reminder;
		reminder = ft_strjoin(reminder, buffer);
		free(tmp);
	}
	free(buffer);
	return (reminder);
}

char	*ft_extract_line(char *reminder)
{
	char	*new_string;
	char	*line;
	size_t	len;

	if (!reminder || *reminder == '\0')
		return (NULL);
	new_string = ft_strchr(reminder, '\n');
	if (!new_string)
		line = ft_substr(reminder, 0, ft_strlen(reminder));
	else
	{
		len = new_string - reminder + 1;
		line = ft_substr(reminder, 0, len);
	}
	return (line);
}

char	*ft_clean_reminder(char	*reminder)
{
	char	*new_string;
	char	*new_reminder;

	if (!reminder)
		return (NULL);
	new_string = ft_strchr(reminder, '\n');
	if (!new_string)
	{
		free(reminder);
		return (NULL);
	}
	new_reminder = ft_substr(reminder, (new_string - reminder + 1),
			ft_strlen(reminder) - (new_string - reminder + 1));
	free(reminder);
	return (new_reminder);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reminder = ft_read_and_fill_reminder(fd, reminder);
	if (!reminder)
		return (NULL);
	line = ft_extract_line(reminder);
	if (!line)
		return (NULL);
	reminder = ft_clean_reminder(reminder);
	return (line);
}
/*int main(void)
{
	int fd = open("file.txt", O_RDONLY);
	char *line;

	if (fd < 0)
		return 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf ("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}*/
