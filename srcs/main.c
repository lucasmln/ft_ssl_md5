#include "../inc/ft_ssl.h"

uint32_t	k[] = { 0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
				0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
				0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
				0x6b901122,0xfd987193,0xa679438e,0x49b40821,
				0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
				0xd62f105d,0x2441453,0xd8a1e681,0xe7d3fbc8,
				0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
				0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
				0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
				0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
				0x289b7ec6,0xeaa127fa,0xd4ef3085,0x4881d05,
				0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
				0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
				0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
				0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
				0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};

uint32_t	r[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
					5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
					4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
					6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };
uint32_t	k[64];

uint32_t	h0 = 0x67452301;
uint32_t	h1 = 0xEFCDAB89;
uint32_t	h2 = 0x98BADCFE;
uint32_t	h3 = 0x10325476;

int		get_bytes_blocs(int size)
{
	return ((size / BLOC_SIZE) + 1 + (size % BLOC_SIZE > 56 ? 1 : 0));
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

void	loop(uint8_t *hash_str, int total_bloc)
{
	//uint8_t		bloc[64];
	//(void
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	*word_bloc;

	for (int x = 0; x < total_bloc; x++)
	{
		word_bloc = (uint32_t *)&hash_str[x * BLOC_SIZE];
		//ft_memcpy(bloc, &hash_str[b * BLOC_SIZE], BLOC_SIZE);
		a = h0;
		b = h1;
		c = h2;
		d = h3;
		for (int i = 0; i < 64; i++)
		{
			if (i < 16)
			{
				f = F(b, c, d);
				g = i;
			}
			else if (i >= 16 && i < 32)
			{
				f = G(b, c, d);
				g = (x * i + 1) % 16;
			}
			else if (i >= 32 && i < 48)
			{
				f = H(b, c, d);
				g = (3 * i + 5) % 16;
			}
			else if (i >= 48 && i < 64)
			{
				f = I(b, c, d);
				g = (7 * i) % 16;
			}
			uint32_t	temp = d;
			d = c;
			c = b;
			b = 
			a = temp;
		}
	}
}

int		main(int ac, char **av)
{
	int		size;
	char	*str;
	int		total_bloc;
	uint8_t	*hash_str;
	uint64_t	*tmp;

	if (ac < 2)
		return (1);
	printf("%s\n", av[1]);
	str = av[1];
	size = ft_strlen(str);
	total_bloc = get_bytes_blocs(size);
	str[size] = 1;
	hash_str = NULL;
	printf("hash : %s/%d/%d\n", hash_str, size, total_bloc);
	if (!(hash_str = malloc(sizeof(uint8_t) * (BLOC_SIZE * total_bloc))))
		fatal();
	ft_memcpy(hash_str, str, ft_strlen(str));
	hash_str[size] = 0b010000000;
	ft_memset(&hash_str[size + 1], 0, BLOC_SIZE * total_bloc - size - 1);
	tmp = (uint64_t *)&hash_str[BLOC_SIZE * total_bloc - 8];
	*tmp = (uint8_t)size * 8;
	for (int i = 0; i < BLOC_SIZE * total_bloc; i++)
	{
		print_bits(hash_str[i]);
		write(1, " ", 1);
	}
	loop(hash_str, total_bloc);
	printf("\n");
	free(hash_str);
//	memset(tmp + siz
	//printf("size : %d, bloc : %d\n, int size : %ld\n", size, total_bloc, sizeof(int));

	return (0);
}
