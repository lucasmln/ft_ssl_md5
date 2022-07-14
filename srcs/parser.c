#include "../inc/ft_ssl.h"

void	print_usage()
{
	putstr("Usage: ./ft_ssl algorithm [options] [file...]\n");
	putstr("\tfile... files to digest (default is stdin)\n");
	putstr("\t-h --help\t\tDisplay this summary\n");
}

char	get_flag(char *flag)
{
	if (ft_strlen(flag) <= 1)
		return (0);
	if (flag[1] == '-')
	{
		if (!ft_strncmp(flag, "--help", ft_strlen("--help")) && ft_strlen("--help") == ft_strlen(flag))
			return ('h');
	}
	return (flag[1]);
}

void	get_options(int ac, char **av, int *i, t_md5 *md5)
{
	switch (get_flag(av[*i]))
	{
		case 'h':
			print_usage();
			exit(0);
			break;
		case 'f':
			(*i)++;
			break;
		case 'I':
			break;
		case 'm':
			break;
		case 'n':
			break;
		case 'p':
			md5->flags = md5->flags | FLAGS_P;
		//	set_flag_ivalue((int *)&md5->default_port, *i + 1, av, ac);
			break;
		case 'q':
			md5->flags = md5->flags | FLAGS_Q;
		//	set_flag_ivalue(&md5->nb_probes, *i + 1, av, ac);
			break;
		case 'r':
			md5->flags = md5->flags | FLAGS_R;
		//	set_flag_ivalue(&md5->nb_probes, *i + 1, av, ac);
			break;
		case 's':
			if (*i + 1 >= ac)
				md5->flags = md5->flags | FLAGS_BAD;
			(*i)++;
			break;
		case 'w':
			break;
		case 'z':
			break;
		default:
			printf("Bad option `%s` (argc %d)\n", av[*i], *i);
			exit(2);
			break;
	}
}

int		parse(char **av, int ac, t_md5 *md5)
{
	int		option_count;

	option_count = 0;
	for (int i = 1; i < ac; i++)
	{
		if (av[i][0] == '-')
		{
			get_options(ac, av, &i, md5);
			option_count++;
		}
		if (md5->flags & FLAGS_BAD)
		{
			putstr("ft_ssl: Error: bad flag\n");
			exit(1);
		}
	}
	return (option_count);
}
