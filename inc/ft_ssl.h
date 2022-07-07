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
# define E 4
# define F 5
# define G 6
# define H 7

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void    print_bits(unsigned char octet);
int		md5_reverse(int i);
int		ft_strlen(char *str);
int		get_bytes_blocs(int size);

void	fatal();



typedef struct		s_md5
{
	int			nb_blocs;
	uint32_t	size;
}					t_md5;

void	loop_sha256(t_md5 *md5, uint32_t *message);
void	exec_sha256(t_md5 md5, char *str);

# define FF(B, C, D)			((B) & (C)) | (~(B) & (D))
# define GG(B, C, D)			((D) & (B)) | ((C) & ~(D))
# define HH(B, C, D)			(B) ^ (C) ^ (D)
# define II(B, C, D)			(C) ^ (B | ~(D))
# define LEFT_ROTATE(x, n)	(((x) << (n)) | ((x) >> (32 - (n))))

void	digest_bloc(uint32_t *abcd, int i, uint32_t *bloc);

#endif
