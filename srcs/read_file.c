#include "../inc/ft_ssl.h"


char	*read_file(int fd, uint32_t *byte_read)
{
	char	buf[1024];
	int		ret;
	char	*tmp;
	char	*message;

	if (!(message = malloc(sizeof(char) * 1)))
		fatal();
	*byte_read = 0;
	while ((ret = read(fd, buf, 1024)) > 0)
	{
		if (!(tmp = malloc(sizeof(char) * (*byte_read + 1))))
			fatal();
		ft_memcpy(tmp, message, *byte_read + 1);
		tmp[*byte_read] = '\0';
		free(message);
		if (!(message = malloc(sizeof(char) * (*byte_read + ret + 1))))
			fatal();
		ft_memcpy(message, tmp, *byte_read);
		ft_memcpy(message + *byte_read, buf, ret);
		*byte_read += ret;
	}
	message[*byte_read] = '\0';
	return (message);
}

char	*get_file_content(char *filename, uint32_t *byte_read)
{
	int		fd;
	char	*message;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		putstr("ft_ssl: ");
		putstr(filename);
		putstr(": No such file or directory\n");
		return (NULL);
	}
	message = read_file(fd, byte_read);
	close(fd);
	return (message);
}
