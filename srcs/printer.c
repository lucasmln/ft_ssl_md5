#include "../inc/ft_ssl.h"

void	print_hex(uint32_t nb)
{
	char	c;
	char	buf[9];
	int		i;

	i = 7;
	while (i >= 0)
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

void	print_hex_64(uint64_t nb)
{
	char	c;
	char	buf[17];
	int		i;

	i = 15;
	while (i >= 0)
	{
		c = nb % 16;
		if (c < 10)
			buf[i--] = c + '0';
		else
			buf[i--] = c - 10 + 'a';
		nb /= 16;
	}
	buf[16] = '\0';
	putstr(buf);
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

void	print_sha512_hash(t_md5 *md5, uint64_t *h, int h_size)
{
	if (!(md5->flags & FLAGS_STDIN) && !(md5->flags & FLAGS_Q))
	{
		if (!(md5->flags & FLAGS_R) && md5->algo == SHA384_ALGO)
			putstr("SHA384 ");
		else if (!(md5->flags &FLAGS_R) && md5->algo == SHA512_ALGO)
			putstr("SHA512 ");
	}
	if (!(md5->flags & FLAGS_R) && !(md5->flags & FLAGS_Q))
		print_filename(md5);
	for (int i = 0; i < h_size; i++)
		print_hex_64(h[i]);
	if (md5->flags & FLAGS_R && !(md5->flags & FLAGS_Q))
	{
		putstr(" ");
		print_filename(md5);
	}
	putstr("\n");
}

void	print_md5_hash(t_md5 *md5, uint32_t *h, int h_size)
{
	if (!(md5->flags & FLAGS_STDIN) && !(md5->flags & FLAGS_Q))
	{
		if (!(md5->flags & FLAGS_R) && md5->algo == MD5_ALGO)
			putstr("MD5 ");
		else if (!(md5->flags &FLAGS_R) && md5->algo == SHA256_ALGO)
			putstr("SHA256 ");
		else if (!(md5->flags &FLAGS_R) && md5->algo == SHA224_ALGO)
			putstr("SHA224 ");
	}
	if (!(md5->flags & FLAGS_R) && !(md5->flags & FLAGS_Q))
		print_filename(md5);
	for (int i = 0; i < h_size; i++)
		print_hex(reverse_int32(h[i]));
	if (md5->flags & FLAGS_R && !(md5->flags & FLAGS_Q))
	{
		putstr(" ");
		print_filename(md5);
	}
	putstr("\n");
}
