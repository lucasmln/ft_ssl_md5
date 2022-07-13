#include "../inc/ft_ssl.h"

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

void	print_bloc_bits(uint8_t *str)
{
	write(1, "BLOC BITS : \n", strlen("BLOC BITS : \n"));
	for (int i = 0; i < 64; i++)
	{
		char c = (i % 26) + 'A';
		write(1, "BLOC BITS : ", strlen("BLOC BITS : "));
		write(1, &c, 1);
		write(1, " ", 1);
		print_bits(str[i]);
		write(1, "\n", 1);
	}
}

int		md5_reverse(int i)
{
	int result;

	result = (i << 24 & 0xff000000) +
		(i << 8 & 0xff0000) +
		(i >> 8 & 0xff00) +
		(i >> 24 & 0xff);
	return (result);
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
		write(1, "usage: ft_ssl command [flags] [file/string]\n", 44);
		// read from stdin
		return (1);
	}
	md5.flags = 0;
	parse(av, ac, &md5);
	printf("flags : %d\n", md5.flags & FLAGS_P);
	algo = get_algo(av[1]);
	if (algo == BAD_ALGO)
	{
		write(1, "ft_ssl: Invalid command '", 25);
		putstr(av[1]);
		write(1, "'; type 'help' for a list.\n", 27);
		return (1);
	}
	if (ac == 2 || (ac > 2 && (md5.flags & FLAGS_P)))
	{
		str = read_file(STDIN_FILENO, &md5.size);
		md5.filename = "stdin";
		if (str)
			launch_algo(algo, md5, str);
		if (md5.flags & FLAGS_P)
		{
			goto _file_hash;
		}
	}
	else
	{
_file_hash:
		for (int i = 2; i < ac; i++)
		{
			str = get_file_content(av[i], &md5.size);
			if (str)
			{
				md5.filename = av[i];
				launch_algo(algo, md5, str);
				free(str);
			}
		}
	}
	return (0);
}
