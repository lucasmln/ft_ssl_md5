# include "../inc/ft_ssl.h"

void	init_sha224_h_value(uint32_t *h)
{
	h[0] = 0xc1059ed8;
	h[1] = 0x367cd507;
	h[2] = 0x3070dd17;
	h[3] = 0xf70e5939;
	h[4] = 0xffc00b31;
	h[5] = 0x68581511;
	h[6] = 0x64f98fa7;
	h[7] = 0xbefa4fa4;
}

void	exec_sha224(t_md5 md5, char *str)
{
	uint8_t	*message;

	message = format_sha256(&md5, (uint32_t *)str);
	loop_sha256(&md5, (uint32_t *)message);
	free(message);
}
