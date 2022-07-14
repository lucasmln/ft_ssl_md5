#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# define BLOC_SIZE		64
# define A				0
# define B				1
# define C				2
# define D				3
# define E				4
# define F				5
# define G				6
# define H				7
# define BAD_ALGO		0
# define MD5_ALGO		1
# define SHA256_ALGO	2
# define FLAGS_P		0b0000001
# define FLAGS_Q		0b0000010
# define FLAGS_R		0b0000100
# define FLAGS_S		0b0001000
# define FLAGS_STDIN	0b0010000
# define FLAGS_END		0b0100000
# define FLAGS_BAD		0b1000000

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void    print_bits(unsigned char octet);
int		md5_reverse(int i);
int		ft_strlen(char *str);
int		get_bytes_blocs(int size);
void	putstr(char *str);
char	*read_file(int fd, uint32_t *byte_read);
char	*get_file_content(char *filename, uint32_t *byte_read);
void	print_hex(uint32_t nb);

void	fatal();



typedef struct		s_md5
{
	int			nb_blocs;
	int			flags;
	int			algo;
	uint32_t	size;
	char		*filename;
	void		(*fct)(struct s_md5, char *);
}					t_md5;

int		parse(char **av, int ac, t_md5 *md5);
void	loop_sha256(t_md5 *md5, uint32_t *message);
void	exec_sha256(t_md5 md5, char *str);
void	exec_md5(t_md5 md5, char *str);
void	loop_m5(t_md5 *md5, uint32_t *str);
void	print_md5_hash(t_md5 *md5, uint32_t *h, int h_size);

void	print_bloc_bits(uint8_t *str);
# define FF(B, C, D)			((B) & (C)) | (~(B) & (D))
# define GG(B, C, D)			((D) & (B)) | ((C) & ~(D))
# define HH(B, C, D)			(B) ^ (C) ^ (D)
# define II(B, C, D)			(C) ^ (B | ~(D))
# define LEFT_ROTATE(x, n)	(((x) << (n)) | ((x) >> (32 - (n))))

void	digest_bloc(uint32_t *abcd, int i, uint32_t *bloc);

#endif
