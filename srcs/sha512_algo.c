# include "../inc/sha512.h"
# include "../inc/ft_ssl.h"

void	init_sha512_h_value(uint64_t *h)
{
	h[0] = 0x6a09e667f3bcc908;
	h[1] = 0xbb67ae8584caa73b;
	h[2] = 0x3c6ef372fe94f82b;
	h[3] = 0xa54ff53a5f1d36f1;
	h[4] = 0x510e527fade682d1;
	h[5] = 0x9b05688c2b3e6c1f;
	h[6] = 0x1f83d9abfb41bd6b;
	h[7] = 0x5be0cd19137e2179;
}


uint64_t	uint64_reverse(uint64_t n)
{
	uint64_t	x;

	x = n;
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
	return (x);
}

uint8_t	*append_sha512(t_md5 *md5, char *str)
{
	uint64_t	msg_size;
	size_t		size_pos;
	uint8_t		*hash_str;
	uint64_t	*tmp;

	md5->nb_blocs = get_bytes_blocs(md5->size);
	if (!(hash_str = malloc(sizeof(uint8_t) * (2 * BLOC_SIZE  * md5->nb_blocs))))
		fatal();
	ft_memset(hash_str, 0, BLOC_SIZE * md5->nb_blocs * 2);
	ft_memcpy(hash_str, str, md5->size);
	hash_str[md5->size] = 0x80;
	int i = -1;
	tmp = (uint64_t *)hash_str;
	printf("tmp[0] : %llx\n", tmp[0]);
	printf("tmp[0] : %.16x\n", (uint32_t)str[1]);
	printf("tmp[0] : %.16x\n", hash_str[0]);
	while (++i < (md5->nb_blocs * 16) - 1)
		tmp[i] = uint64_reverse(tmp[i]);
	printf("tmp[0] : %llx\n", tmp[0]);
	printf("tmp[0] : %.16x\n", hash_str[0]);
	msg_size = md5->size * 8;
	size_pos = (BLOC_SIZE * md5->nb_blocs * 2) - 8;
	ft_memcpy(hash_str + size_pos, &msg_size, sizeof(uint64_t));
	return (hash_str);
}

void	fill_tmp_word_sha512(uint64_t *tmp_word, uint64_t *word)
{
	uint64_t	s0;
	uint64_t	s1;

	ft_memcpy(tmp_word, word, 17 * sizeof(uint64_t) );
	for (int t = 16; t < 80; t++)
	{
		s0 = SSIG0(tmp_word[t - 15]);
		s1 = SSIG1(tmp_word[t - 2]);
		tmp_word[t] = tmp_word[t - 16] + s0 + tmp_word[t - 7] + s1;
	}
}

void	digest_sha512(uint64_t *tmp_word, uint64_t *abcd)
{
	uint64_t	t1;
	uint64_t	t2;

	for (uint64_t t = 0; t < 80; t++)
	{
		t1 = abcd[H] + BSIG1(abcd[E]) + CH(abcd[E], abcd[F], abcd[G]) + sha512_k[t] + tmp_word[t];
		t2 = BSIG0(abcd[A]) + MAJ(abcd[A], abcd[B], abcd[C]);
		abcd[H] = abcd[G];
		abcd[G] = abcd[F];
		abcd[F] = abcd[E];
		abcd[E] = abcd[D] + t1;
		abcd[D] = abcd[C];
		abcd[C] = abcd[B];
		abcd[B] = abcd[A];
		abcd[A] = t1 + t2;
	}
}

void	loop_sha512(t_md5 *md5, uint8_t *message)
{
	uint64_t	*word;
	uint64_t	abcd[8];
	uint64_t	tmp_word[80];
	uint64_t	h[8];

	init_sha512_h_value(h);
	ft_memset(tmp_word, 0, 80);
	for (int x = 0; x < md5->nb_blocs; x++)
	{
		word = (uint64_t *)(message + x * 16/*BLOC_SIZE*/);
		fill_tmp_word_sha512(tmp_word, (uint64_t *)(message + x * 128));
		for (int i = 0; i < 8; i++)
			abcd[i] = h[i];
		digest_sha512(tmp_word, abcd);
		for (int i = 0; i < 8; i++)
			h[i] += abcd[i];
	}
	for (int i = 0; i < 8; i++)
		printf("%.16llx", h[i]);
	printf("\n");
	//print_md5_hash(md5, h, md5->algo == SHA256_ALGO ? 8 : 7);
}

void	exec_sha512(t_md5 md5, char *str)
{
	uint8_t	*message;

	message = append_sha512(&md5, str);
	loop_sha512(&md5, message);
	free(message);
}
