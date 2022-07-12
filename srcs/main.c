#include "../inc/ft_ssl.h"
#include "../inc/md5.h"

int		md5_reverse(int i)
{
	int result;

	result = (i << 24 & 0xff000000) +
		(i << 8 & 0xff0000) +
		(i >> 8 & 0xff00) +
		(i >> 24 & 0xff);
	return (result);
}

void	init_md5_h_value(uint32_t *h)
{
	h[0] = 0x67452301;
	h[1] = 0xefcdab89;
	h[2] = 0x98badcfe;
	h[3] = 0x10325476;
}

void	putstr(char *str)
{
	write(1, str, ft_strlen(str));
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
	for (int i = 0; i < 4; i++)
		printf("%.8x", md5_reverse(h[i]));
	printf("\n");
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

void	exec_md5(t_md5 md5, char *str)
{
	uint8_t	*hash_str;

	hash_str = format_message(&md5, str);
	loop(&md5, (uint32_t *)hash_str);
	free(hash_str);
}

char	*put_lower_case(char *str)
{
	char	*str_lower;

	if (!(str_lower = malloc(sizeof(char) * ft_strlen(str))))
		fatal();
	for (int i = 0; i < ft_strlen(str); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str_lower[i] = str[i] + 32;
		else
			str_lower[i] = str[i];
	}
	return (str_lower);
}

int		get_algo(char *algo_name)
{
	char	*lower_case_algo;
	int		cmp_len;
	int		algo;

	lower_case_algo = put_lower_case(algo_name);
	cmp_len = ft_strlen(lower_case_algo) < 6 ? 6 : ft_strlen(lower_case_algo);
	if (!ft_strncmp(lower_case_algo, "md5", cmp_len))
		algo = MD5_ALGO;
	else if (!ft_strncmp(lower_case_algo, "sha256", cmp_len))
		algo = SHA256_ALGO;
	else
		algo = BAD_ALGO;
	free(lower_case_algo);
	return (algo);
}

void	launch_algo(int algo, t_md5 md5, char *str)
{
	switch (algo)
	{
		case MD5_ALGO:
			exec_md5(md5, str);
			break;
		case SHA256_ALGO:
			exec_sha256(md5, str);
	}
}

int		main(int ac, char **av)
{
	char		*str;
	t_md5		md5;
	int			algo;

	if (ac <= 1)
	{
		// read from stdin
		return (1);
	}
	algo = get_algo(av[1]);
	if (algo == BAD_ALGO)
	{
		write(1, "ft_ssl: Invalid command '", 25);
		putstr(av[1]);
		write(1, "'; type 'help' for a list.\n", 27);
		return (1);
	}
	if (ac == 2)
	{
		str = read_file(STDIN_FILENO);
		launch_algo(algo, md5, str);
	}
	else
	{
		for (int i = 2; i < ac; i++)
		{
			str = get_file_content(av[i]);
			launch_algo(algo, md5, str);
			free(str);
		}
	}
	return (0);
}
