#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define BLOC_SIZE 64

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

uint32_t	f;
uint32_t	g;

# define F(B, C, D)			(B & C) | ((!B) & D)
# define G(B, C, D)			(D & B) | ((!D) & C)
# define H(B, C, D)			B ^ C ^ D
# define I(B, C, D)			C ^ (B | (!D))
# define LEFT_ROTATE(x, n)	((x << n) | (x >> (32 - n))) 

#endif
