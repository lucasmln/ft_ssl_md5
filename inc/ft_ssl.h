#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define BLOC_SIZE 64
# define A 0
# define B 1
# define C 2
# define D 3

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(const char *s1);
void    print_bits(unsigned char octet);


typedef struct		s_md5
{
	int			nb_blocs;
	uint32_t	size;
}					t_md5;

# define F(B, C, D)			((B) & (C)) | (~(B) & (D))
# define G(B, C, D)			((D) & (B)) | ((C) & ~(D))
# define H(B, C, D)			(B) ^ (C) ^ (D)
# define I(B, C, D)			(C) ^ (B | ~(D))
# define LEFT_ROTATE(x, n)	(((x) << (n)) | ((x) >> (32 - (n))))

void	digest_bloc(uint32_t *abcd, int i, uint32_t *bloc);

#endif
