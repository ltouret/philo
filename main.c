#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

# define ERR_MSG "Error : Invalid Arguments"
# define ERR 0
# define OK 1

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ERR);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (ERR);
		i++;
	}
	return (OK);
}

int	check_args(int argc, char *argv[])
{
	int	i;

	if ((argc == 5 || argc == 6) && check_args_digit(char *argv[]))
	{
		i = 1;
		while (i < argc)
		{
			if (ft_isdigit(argv[i]) == ERR)
			{
				printf("%s\n", ERR_MSG);
				return (ERR);
			}
			i++;
		}
	}
	else
	{
		printf("%s\n", ERR_MSG);
		return (ERR);
	}
	return (OK);
}

int	main(int argc, char *argv[])
{
	if (check_args(argc, argv) == ERR)
		return (1);
	return (0);
}
