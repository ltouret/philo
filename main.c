#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

# define ERR_MSG "Error : Invalid Arguments"
# define ERR 0
# define OK 1

typedef struct	s_arg
{
	int		total;
	int		die;
	int		eat;
	int		sleep;
	int		max_eat;
}				t_arg;

typedef struct	s_phi
{
}				t_phi;

typedef struct	s_data
{
	t_arg	arg;
	t_phi	*phi;
}				t_data;

int	slen(char *s)
{
	int	i;
	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_atol(char *s)
{
	long	num;
	int		i;

	if (!s)
		return (0);
	num = 0;
	i = 0;
	while (s[i])
	{
		num = (s[i] - 48) + (num * 10);
		i++;
	}
	return (num);
}

int	check_args_digit(int argc, char *argv[])
{
	int		i;
	int		o;
	char	c;

	i = 1;
	while (i < argc)
	{
		o = 0;
		if (slen(argv[i]) == 0 || slen(argv[i]) > 10)
			return (ERR);
		while (argv[i][o])
		{
			c = argv[i][o];
			if (!(c >= '0' && c <= '9'))
				return (ERR);
			o++;
		}
		i++;
	}
	return (OK);
}

int	check_args(int argc, char *argv[], t_data *data)
{
	if ((argc == 5 || argc == 6) && check_args_digit(argc, argv) == OK)
	{
		data->arg.total = ft_atol(argv[1]);
		data->arg.die = ft_atol(argv[2]);
		data->arg.eat = ft_atol(argv[3]);
		data->arg.sleep = ft_atol(argv[4]);
		data->arg.max_eat = -1;
		if (argc == 6)
			data->arg.max_eat = ft_atol(argv[5]);
		// TODO maybe [max_eat] could be 0 and just print that each philo eat 0 time(s)?
		if (data->arg.total <= 0 || data->arg.die <= 0 || data->arg.eat <= 0
				|| data->arg.sleep <= 0
				|| (data->arg.max_eat <= 0 && argc == 6))
			return (ERR);
	}
	else
		return (ERR);
	return (OK);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (check_args(argc, argv, &data) == ERR)
	{
		printf("%s\n", ERR_MSG);
		return (1); // ret error? ERR is 0 tho
	}
	return (0);
}
