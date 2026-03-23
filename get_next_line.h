#ifndef GETNEXTLINE_H
#define GETNEXTLINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const  *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_readAndFillReminder(int fd, char *reminder);
char	*ft_extract_line(char *reminder);
char	*ft_clean_reminder(char *reminder);
char	*get_next_line(int fd);
#endif
