#include "../inc/ft_ssl.h"

void	init_sha384_h_value(uint64_t *h)
{
	h[0] = 0xcbbb9d5dc1059ed8;
	h[1] = 0x629a292a367cd507;
	h[2] = 0x9159015a3070dd17;
	h[3] = 0x152fecd8f70e5939;
	h[4] = 0x67332667ffc00b31;
	h[5] = 0x8eb44a8768581511;
	h[6] = 0xdb0c2e0d64f98fa7;
	h[7] = 0x47b5481dbefa4fa4;
}

void	exec_sha384(t_md5 md5, char *str)
{
	uint8_t	*message;

	message = format_sha512(&md5, str);
	loop_sha512(&md5, message);
	free(message);
}
