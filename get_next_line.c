#include "get_next_line.h"
#include <stdio.h>

char	*ft_readAndFillReminder(int fd, char *reminder)
{
	int	read_bytes;
	char	*buffer;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
        	return NULL;
	read_bytes = 1;
	while(!ft_strchr(reminder,'\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(buffer);
			return NULL;
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
	new_string = ft_strchr(reminder,'\n');
	if (!new_string)
		line = ft_substr(reminder, 0 , strlen(reminder));
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
	new_string = ft_strchr(reminder,'\n');
	if (!new_string)
	{
		free(reminder);
		return (NULL);
	}
	new_reminder = ft_substr(reminder,(new_string - reminder + 1), ft_strlen(reminder) - (new_string - reminder + 1));
	free(reminder);
	return (new_reminder);
}
char	*get_next_line(int fd)
{
	static	char *reminder;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reminder = ft_readAndFillReminder(fd, reminder);
	if (!reminder)
		return NULL;
	line = ft_extract_line(reminder);
	if (!line)
		return NULL;
	reminder = ft_clean_reminder(reminder);
	return (line);
}

int main(void)
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
}
