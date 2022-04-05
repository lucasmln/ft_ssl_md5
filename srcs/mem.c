#include <stdlib.h>

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
