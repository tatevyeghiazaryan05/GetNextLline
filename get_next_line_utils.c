#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t  ft_strlen(const char *s)
{
        size_t  i;

        i = 0;
        while(s[i] != '\0')
                i++;
        return (i);
}
char    *ft_strchr(const char *s, int c)
{
        int     i;

        i = 0;
        while(s[i] != c && s[i] != '\0')
                i++;
        return (char *)(&s[i]);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
        i = 0;
	if (size == 0)
		return(src_len + dst_len);
	if (dst_len >= size)
		return (src_len + size);
	while (src[i] && i + dst_len < size - 1)
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (dst_len + src_len);
}
char	*ft_strjoin(char const  *s1, char const *s2)
{
	int	len_s1;
	int	len_s2;

	char	*new_string;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_string = (char *) malloc(len_s1 + len_s2 + 1);
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s1,len_s1 + 1);
	ft_strlcat(new_string,s2, len_s1+ len_s2 + 1);
	return (new_string);
}
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

int main() {
    char *s1 = "Hello";
    char *s2 = "World";
    printf("%s", ft_strjoin(s1, s2));
    return (0);
}
