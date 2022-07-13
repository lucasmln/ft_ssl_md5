# include "../inc/ft_ssl.h"
# include "../inc/md5.h"

void	init_md5_h_value(uint32_t *h)
{
	h[0] = 0x67452301;
	h[1] = 0xefcdab89;
	h[2] = 0x98badcfe;
	h[3] = 0x10325476;
}

void	print_filename(t_md5 *md5)
{
	if (!(md5->flags & FLAGS_R))
		putstr("(");
	if ((md5->flags & FLAGS_P) || (md5->flags & FLAGS_S))
		putstr("\"");
	putstr(md5->filename);
	if ((md5->flags & FLAGS_P) || (md5->flags & FLAGS_S))
		putstr("\"");
	if (!(md5->flags & FLAGS_R))
		putstr(") = ");
}

void	print_hex(uint32_t nb)
{
	char	c;
	char	buf[9];
	int		i;

	i = 7;
	while (nb > 0)
	{
		c = nb % 16;
		if (c < 10)
			buf[i--] = c + '0';
		else
			buf[i--] = c - 10 + 'a';
		nb /= 16;
	}
	buf[8] = '\0';
	putstr(buf);
}

void	print_md5_hash(t_md5 *md5, uint32_t *h, int h_size)
{
	if (!(md5->flags & FLAGS_STDIN))
	{
		if (!(md5->flags & FLAGS_R) && md5->algo & MD5_ALGO)
			putstr("MD5 ");
		else if (!(md5->flags &FLAGS_R) && md5->algo & SHA256_ALGO)
			putstr("SHA256 ");
	}
	if (!(md5->flags & FLAGS_R))
		print_filename(md5);
	for (int i = 0; i < h_size; i++)
		print_hex(md5_reverse(h[i]));
	if (md5->flags & FLAGS_R)
	{
		putstr(" ");
		print_filename(md5);
	}
	putstr("\n");
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
		f = FF(abcd[B], abcd[C], abcd[D]);
		g = i;
	}
	else if (i >= 16 && i < 32)
	{
		f = GG(abcd[B], abcd[C], abcd[D]);
		g = (5 * i + 1) % 16;
	}
	else if (i >= 32 && i < 48)
	{
		f = HH(abcd[B], abcd[C], abcd[D]);
		g = (3 * i + 5) % 16;
	}
	else if (i >= 48 && i < 64)
	{
		f = II(abcd[B], abcd[C], abcd[D]);
		g = (7 * i) % 16;
	}
	f += abcd[A] + k[i] + bloc[g];
	switch_abcd(abcd, f, i);
}

void	loop(t_md5 *md5, uint32_t *hash_str)
{
	uint32_t	*word_bloc;
	uint32_t	abcd[4];
	uint32_t	h[4];

	init_md5_h_value(h);
	for (int x = 0; x < md5->nb_blocs; x++)
	{
		word_bloc = (uint32_t *)(hash_str + x * BLOC_SIZE / 4);
		abcd[A] = h[0];
		abcd[B] = h[1];
		abcd[C] = h[2];
		abcd[D] = h[3];
		for (int i = 0; i < 64; i++)
			digest_bloc(abcd, i, word_bloc);
		h[0] += abcd[A];
		h[1] += abcd[B];
		h[2] += abcd[C];
		h[3] += abcd[D];
	}
	print_md5_hash(md5, h, 4);
}

uint8_t		*format_message(t_md5 *md5, char *message)
{
	uint32_t	msg_size;
	size_t		size_pos;
	uint8_t		*hash_str;

	md5->nb_blocs = get_bytes_blocs(md5->size);
	if (!(hash_str = malloc(sizeof(uint8_t) * (BLOC_SIZE * md5->nb_blocs))))
		fatal();
	ft_memset(hash_str, 0, BLOC_SIZE * md5->nb_blocs);
	ft_memcpy(hash_str, message, md5->size);
	hash_str[md5->size] = 0b010000000;
	msg_size = md5->size * 8;
	size_pos = BLOC_SIZE * md5->nb_blocs - 8;
	ft_memcpy(hash_str + size_pos, &msg_size, 4);
	return (hash_str);
}

void	exec_md5(t_md5 md5, char *str)
{
	uint8_t	*hash_str;

	hash_str = format_message(&md5, str);
	loop(&md5, (uint32_t *)hash_str);
	free(hash_str);
}
