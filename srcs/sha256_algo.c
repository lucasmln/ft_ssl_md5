# include "../inc/ft_ssl.h"
# include "../inc/sha256.h"
# include <string.h>

uint32_t		swap_int32(const uint32_t value)
{
	uint32_t result;

	result = 0;
	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return (result);
}

uint8_t	*append_sha256(t_md5 *md5, uint32_t *message)
{
	uint32_t	msg_size;
	size_t		size_pos;
	uint8_t		*hash_str;
	uint32_t	*tmp;

	md5->nb_blocs = get_bytes_blocs(md5->size);
	if (!(hash_str = malloc(sizeof(uint8_t) * (BLOC_SIZE * md5->nb_blocs))))
		fatal();
	ft_memcpy(hash_str, message, md5->size);
	hash_str[md5->size] = 0b010000000;
	int i = -1;
	tmp = (uint32_t *)hash_str;
	while (i++ < (md5->nb_blocs * 16) - 1)
		tmp[i] = md5_reverse((uint32_t)tmp[i]);
	msg_size = md5->size * 8;
	size_pos = (BLOC_SIZE * md5->nb_blocs) - 4;
	ft_memcpy(hash_str + size_pos, &msg_size, sizeof(uint32_t));
	return (hash_str);
}

void	init_h_value(uint32_t *h)
{
	h[0] = 0x6a09e667;
	h[1] = 0xbb67ae85;
	h[2] = 0x3c6ef372;
	h[3] = 0xa54ff53a;
	h[4] = 0x510e527f;
	h[5] = 0x9b05688c;
	h[6] = 0x1f83d9ab;
	h[7] = 0x5be0cd19;
}

void	fill_tmp_word(uint32_t *tmp_word, uint32_t *word)
{
	uint32_t	s0;
	uint32_t	s1;

	ft_memcpy(tmp_word, word, 16 * sizeof(uint32_t) );
	for (int t = 16; t < 64; t++)
	{
		s0 = SIGMA0(tmp_word[t - 15]);
		s1 = SIGMA1(tmp_word[t - 2]);
		tmp_word[t] = tmp_word[t - 16] + s0 + tmp_word[t - 7] + s1;
	}
}

void	digest_sha256(uint32_t *tmp_word, uint32_t *abcd)
{
	uint32_t	t1;
	uint32_t	t2;

	for (int t = 0; t < 64; t++)
	{
		t1 = abcd[H] + MAJ_SIGMA1(abcd[E]) + CH(abcd[E], abcd[F], abcd[G]) + sha256_k[t] + tmp_word[t];
		t2 = MAJ_SIGMA0(abcd[A]) + MAJ(abcd[A], abcd[B], abcd[C]);
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

void	loop_sha256(t_md5 *md5, uint32_t *message)
{
	uint32_t	*word;
	uint32_t	abcd[8];
	uint32_t	tmp_word[64];
	uint32_t	h[8];

	init_h_value(h);
	for (int x = 0; x < md5->nb_blocs; x++)
	{
		word = (uint32_t *)(message + x * 16/*BLOC_SIZE*/);
		fill_tmp_word(tmp_word, message + x * 16);
		for (int i = 0; i < 8; i++)
			abcd[i] = h[i];
		digest_sha256(tmp_word, abcd);
		for (int i = 0; i < 8; i++)
			h[i] += abcd[i];
	}
	for (int i = 0; i < 8; i++)
		printf("%.8x", h[i]);
}

void	exec_sha256(t_md5 md5, char *str)
{
	uint8_t	*message;

	message = append_sha256(&md5, (uint32_t *)str);
	loop_sha256(&md5, (uint32_t *)message);
	free(message);
}
