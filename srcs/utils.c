#include "../inc/ft_ssl.h"

uint32_t	reverse_int32(uint32_t i)
{
	int result;

	result = (i << 24 & 0xff000000) +
		(i << 8 & 0xff0000) +
		(i >> 8 & 0xff00) +
		(i >> 24 & 0xff);
	return (result);
}

uint64_t	reverse_int64(uint64_t n)
{
	uint64_t	x;

	x = n;
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
	return (x);
}

void		putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void		fatal()
{
	write(2, "Fatal error: malloc() failed\n", 29);
	exit(2);
}

void		print_bits(unsigned char octet)
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

void	print_bloc_bits(uint8_t *str)
{
	write(1, "BLOC BITS : \n", strlen("BLOC BITS : \n"));
	for (int i = 0; i < 128; i++)
	{
		char c = (i % 26) + 'A';
		write(1, "BLOC BITS : ", strlen("BLOC BITS : "));
		write(1, &c, 1);
		write(1, " ", 1);
		print_bits(str[i]);
		write(1, "\n", 1);
	}
}


