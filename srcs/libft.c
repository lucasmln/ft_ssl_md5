#include <stdlib.h>

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		len;
	int		i;

	if (!s1)
		return (NULL);
	len = 0;
	while (s1[len])
		len++;
	copy = malloc((len + 1) * sizeof(char));
	if (copy != NULL)
	{
		i = 0;
		while (s1[i])
		{
			copy[i] = s1[i];
			i++;
		}
		copy[i] = '\0';
		return (copy);
	}
	return (NULL);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				res;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (res != 0)
			return (res);
		i++;
	}
	return (0);
}



void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	i = 0;
	while (n-- > 0)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	char			*tab;

	i = 0;
	tab = (char*)b;
	while (i < len)
	{
		*tab = c;
		tab++;
		i++;
	}
	return (b);
}
