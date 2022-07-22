#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>

# define BLOC_SIZE_512	64
# define BLOC_SIZE_1024	128
# define BUF_SIZE		1000000000
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
# define SHA224_ALGO	3
# define SHA512_ALGO	4
# define SHA384_ALGO	5
# define FLAGS_P		0b0000001
# define FLAGS_Q		0b0000010
# define FLAGS_R		0b0000100
# define FLAGS_S		0b0001000
# define FLAGS_STDIN	0b0010000
# define FLAGS_END		0b0100000
# define FLAGS_BAD		0b1000000

typedef struct		s_md5
{
	int			nb_blocs;
	int			flags;
	int			algo;
	uint32_t	size;
	char		*filename;
}					t_md5;

/*
 ** main.c
*/
int			get_bytes_blocs(int size, int bloc_size);
char		*put_lower_case(char *str);
int			get_algo(char *algo_name);
void		launch_algo(t_md5 md5, char *str);

/*
 ** parser.c
*/
void		print_hex(uint32_t nb);
void		print_hex_64(uint64_t nb);
void		print_filename(t_md5 *md5);
void		print_sha512_hash(t_md5 *md5, uint64_t *h, int h_size);
void		print_md5_hash(t_md5 *md5, uint32_t *h, int h_size);

/*
 ** utils.c
*/
uint64_t	reverse_int64(uint64_t n);
uint32_t	reverse_int32(uint32_t i);
void		putstr(char *str);
void		fatal();

/*
 ** mem.c
*/
int			ft_strlen(char *str);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);

/*
 ** read_file.c
*/
char		*read_file(int fd, uint32_t *byte_read);
char		*get_file_content(char *filename, uint32_t *byte_read);

/*
 ** parser.c
*/
void		print_usage();
char		get_flag(char *flag);
void		get_options(int ac, char **av, int *i, t_md5 *md5);
int			parse(char **av, int ac, t_md5 *md5);

/*
 ** md5_algo.c
*/
void		init_md5_h_value(uint32_t *h);
void		switch_abcd(uint32_t *abcd, uint32_t f, int i);
void		digest_bloc(uint32_t *abcd, int i, uint32_t *bloc);
void		loop(t_md5 *md5, uint32_t *hash_str);
uint8_t		*format_message(t_md5 *md5, char *message);
void		exec_md5(t_md5 md5, char *str);

/*
 ** sha256_algo.c
*/
void		init_h_value(uint32_t *h);
uint8_t		*format_sha256(t_md5 *md5, uint32_t *message);
void		fill_tmp_word(uint32_t *tmp_word, uint32_t *word);
void		digest_sha256(uint32_t *tmp_word, uint32_t *abcd);
void		loop_sha256(t_md5 *md5, uint32_t *message);
void		exec_sha256(t_md5 md5, char *str);

/*
 ** sha224_algo.c
*/
void		init_sha224_h_value(uint32_t *h);
void		exec_sha224(t_md5 md5, char *str);

/*
 ** sha512_algo.c
*/
void		init_sha512_h_value(uint64_t *h);
uint8_t		*format_sha512(t_md5 *md5, char *str);
void		fill_tmp_word_sha512(uint64_t *tmp_word, uint64_t *word);
void		digest_sha512(uint64_t *tmp_word, uint64_t *abcd);
void		loop_sha512(t_md5 *md5, uint8_t *message);
void		exec_sha512(t_md5 md5, char *str);

/*
 ** sha384_algo.c
*/
void		init_sha384_h_value(uint64_t *h);
void		exec_sha384(t_md5 md5, char *str);

void	print_bloc_bits(uint8_t *str);

#endif
