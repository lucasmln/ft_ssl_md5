#include "../inc/ft_ssl.h"
#include "../inc/md5.h"

uint32_t	h0 = 0x67452301;
uint32_t	h1 = 0xefcdab89;
uint32_t	h2 = 0x98badcfe;
uint32_t	h3 = 0x10325476;

int		md5_reverse(int i)
{
	int result;

	result = (i << 24 & 0xff000000) +
		(i << 8 & 0xff0000) +
		(i >> 8 & 0xff00) +
		(i >> 24 & 0xff);
	return (result);
}

int		get_bytes_blocs(int size)
{
	return ((size / BLOC_SIZE) + 1 + (size % BLOC_SIZE >= 56 ? 1 : 0));
}

void	fatal()
{
	write(2, "Fatal error: malloc() failed\n", 29);
	exit(2);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_bloc_bits(uint8_t *str)
{
	write(1, "BLOC BITS : ", ft_strlen("BLOC BITS : "));
	for (int i = 0; i < BLOC_SIZE; i++)
	{
		char c = (i % 26) + 'A';
		write(1, "BLOC BITS : ", ft_strlen("BLOC BITS : "));
		write(1, &c, 1);
		write(1, " ", 1);
		print_bits(str[i]);
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

void    print_bits(unsigned char octet)
{
	int z = 128, oct = octet;

	while (z > 0)
	{
		if (oct & z)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		z >>= 1;
	}
}

void	loop(t_md5 *md5, uint32_t *hash_str)
{
	uint32_t	*word_bloc;
	uint32_t	abcd[4];

	for (int x = 0; x < md5->nb_blocs; x++)
	{
		word_bloc = (uint32_t *)(hash_str + x * BLOC_SIZE / 4);
		abcd[A] = h0;
		abcd[B] = h1;
		abcd[C] = h2;
		abcd[D] = h3;
		for (int i = 0; i < 64; i++)
			digest_bloc(abcd, i, word_bloc);
		h0 += abcd[A];
		h1 += abcd[B];
		h2 += abcd[C];
		h3 += abcd[D];
	}
	printf("\n%.8x%.8x%.8x%.8x\n", md5_reverse(h0), md5_reverse(h1), md5_reverse(h2), md5_reverse(h3));
}

void	switch_abcd(uint32_t *abcd, uint32_t f, int i)
{
	uint32_t	temp;

	temp = abcd[D];
	abcd[D] = abcd[C];
	abcd[C] = abcd[B];
	abcd[B] += LEFT_ROTATE(f, r[i]);
	abcd[A] = temp;
}

void	digest_bloc(uint32_t *abcd, int i, uint32_t *bloc)
{
	uint32_t	g;
	uint32_t	f;

	if (i < 16)
	{
		f = F(abcd[B], abcd[C], abcd[D]);
		g = i;
	}
	else if (i >= 16 && i < 32)
	{
		f = G(abcd[B], abcd[C], abcd[D]);
		g = (5 * i + 1) % 16;
	}
	else if (i >= 32 && i < 48)
	{
		f = H(abcd[B], abcd[C], abcd[D]);
		g = (3 * i + 5) % 16;
	}
	else if (i >= 48 && i < 64)
	{
		f = I(abcd[B], abcd[C], abcd[D]);
		g = (7 * i) % 16;
	}
	f += abcd[A] + k[i] + bloc[g];
	switch_abcd(abcd, f, i);
}

uint8_t		*format_message(t_md5 *md5, char *message)
{
	uint32_t	msg_size;
	size_t		size_pos;
	uint8_t		*hash_str;

	md5->size = ft_strlen(message);
	md5->nb_blocs = get_bytes_blocs(md5->size);
	if (!(hash_str = malloc(sizeof(uint8_t) * (BLOC_SIZE * md5->nb_blocs))))
		fatal();
	ft_memcpy(hash_str, message, ft_strlen(message));
	hash_str[md5->size] = 0b010000000;
	msg_size = md5->size * 8;
	size_pos = BLOC_SIZE * md5->nb_blocs - 8;
	ft_memcpy(hash_str + size_pos, &msg_size, 4);
	return (hash_str);
}

int		main(int ac, char **av)
{
	char	*str;
	uint8_t	*hash_str;
	t_md5		md5;

	if (ac < 2)
		return (1);
// temporaire, le temps de faire le parser correctement
	if (!(str = malloc(sizeof(char) * ft_strlen(av[1]) + 2)))
		return (1);
	for (int i = 0; i < ft_strlen(av[1]); i++)
		str[i] = av[1][i];
	str[ft_strlen(av[1])] = '\n';
	str[ft_strlen(av[1]) + 1] = '\0';

	hash_str = format_message(&md5, str);
	loop(&md5, (uint32_t *)hash_str);
	free(hash_str);
	return (0);
}
