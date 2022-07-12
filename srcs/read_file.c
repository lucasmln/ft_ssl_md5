#include "../inc/ft_ssl.h"


char	*read_file(int fd)
{
	char	buf[1024];
	int		ret;
	int		total_read;
	char	*tmp;
	char	*message;

	if (!(message = malloc(sizeof(char) * 1)))
		fatal();
	total_read = 0;
	while ((ret = read(fd, buf, 1024)) > 0)
	{
		if (!(tmp = malloc(sizeof(char) * (total_read + 1))))
			fatal();
		ft_memcpy(tmp, message, total_read + 1);
		tmp[total_read] = '\0';
		free(message);
		if (!(message = malloc(sizeof(char) * (total_read + ret + 1))))
			fatal();
		ft_memcpy(message, tmp, total_read);
		ft_memcpy(message + total_read, buf, ret);
		total_read += ret;
	}
	message[total_read] = '\0';
	return (message);
}

char	*get_file_content(char *filename)
{
	int		fd;
	int		ret;
	char	*message;
	char	*tmp;
	char	buf[1024];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		putstr("ft_ssl: ");
		putstr(filename);
		putstr(": No such file or directory\n");
		return (NULL);
	}
	return (read_file(fd));
}
