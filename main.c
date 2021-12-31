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
	//TODO rename die to death
	int			total;
	int			die;
	int			eat;
	int			sleep;
	int			max_eat;
	long int	start_t;
}				t_arg;

typedef struct	s_phi
{
	int				nb;
	pthread_t		th_id;
	pthread_mutex_t	*rf;
	pthread_mutex_t	lf;
	t_arg			*arg;
	long int		ms_eat;
	int				nb_eat;
	int				*stop;
}				t_phi;

typedef struct	s_data
{
	t_arg	arg;
	t_phi	*phi;
}				t_data;

long int	act_time(void)
{
	struct timeval	current_time;
	long int		time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (1);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

void		ft_usleep(long int time)
{
	long int	start;

	start = act_time();
	while (act_time() - start < time)
		usleep(time / 10);
}

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
	char		c;

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
		if (data->arg.total <= 0 || data->arg.die <= 0 || data->arg.eat <= 0
				|| data->arg.sleep <= 0)
			return (ERR);
	}
	else
		return (ERR);
	return (OK);
}

int		status(t_phi *phi, int mov)
{
	long int	time;

	if (*phi->stop > 0)
		return (ERR);
	time = act_time() - phi->arg->start_t;
	if (mov == 1)
		printf("%ld %d has taken a fork\n", time, phi->nb + 1);
	if (mov == 2)
		printf("%ld %d is eating\n", time, phi->nb + 1);
	if (mov == 3)
		printf("%ld %d is sleeping\n", time, phi->nb + 1);
	if (mov == 4)
		printf("%ld %d is thinking\n", time, phi->nb + 1);
	return (OK);
}

void	*th_phi(t_phi *phi)
{
	// TODO add protection if only 1 philo!
	if (phi->nb % 2 == 1)
		ft_usleep(phi->arg->eat / 10);
	while (1)
	{
		// TODO first if doesnt solve in case philo eats multiple times mroe and dies cos he cant eat cos blocked by this if!!!
		if (phi->arg->max_eat != -1 && phi->nb_eat >= phi->arg->max_eat)
			continue;
		pthread_mutex_lock(&phi->lf);
		if (status(phi, 1) == ERR)
			break;
		pthread_mutex_lock(phi->rf);
		if (status(phi, 1) == ERR)
			break;
		if (status(phi, 2) == ERR)
			break;
		phi->nb_eat++;
		// sleep & then eat | eat & then sleep?
		ft_usleep(phi->arg->eat);
		phi->ms_eat = act_time();
		//printf("phi %d ate at %ld dies at %ld\n", phi->nb + 1, phi->ms_eat - phi->arg->start_t, phi->ms_eat - phi->arg->start_t + phi->arg->die);
		//TODO this should break my print status
		pthread_mutex_unlock(phi->rf);
		pthread_mutex_unlock(&phi->lf);
		if (status(phi, 3) == ERR)
			break;
		ft_usleep(phi->arg->sleep);
		if (status(phi, 4) == ERR)
			break;
	}
	return (NULL);
}

int	init(t_data *data, int *stop)
{
	int	i;

	i = -1;
	data->arg.start_t = act_time();
	//data->arg.done = 0;
	while (++i < data->arg.total)
	{
		// create each thread of phi here
		data->phi[i].nb = i ;
		data->phi[i].ms_eat = data->arg.start_t;
		data->phi[i].nb_eat = 0;
		data->phi[i].rf = NULL;
		data->phi[i].stop = stop;
		//printf("a %d\n", data->phi[i].nb);
		if (pthread_mutex_init(&(data->phi[i].lf), NULL))
			return (ERR);
		if (data->arg.total == 1)
			return (OK);
		if (i == data->arg.total - 1)
			data->phi[i].rf = &data->phi[0].lf;
		else
			data->phi[i].rf = &data->phi[i + 1].lf;
	}
	i = -1;
	while (++i < data->arg.total)
	{
		//write(1, "X\n", 2);
		data->phi[i].arg = &data->arg;
		if (pthread_create(&data->phi[i].th_id, NULL, (void *)th_phi, &data->phi[i]))
			return (ERR);
	}
	return (OK);
}

int		phy_loop(t_data *data)
{
	int			i;
	long int	time;

	i = 0;
	time = act_time();
	while (i < data->arg.total)
	{
		//printf("%ld\n", time - data->phi[i].ms_eat);
		if (time - data->phi[i].ms_eat >= data->arg.die)
		{
			printf("%ld %d has died\n", time - data->arg.start_t, data->phi[i].nb + 1);
			*data->phi[0].stop = 1;
			return (ERR);
		}
		i++;
	}
	if (data->arg.max_eat != -1)
	{
		i = 0;
		while (i < data->arg.total)
		{
			if (data->phi[i].nb_eat < data->arg.max_eat)
				break;
			i++;
		}
		if (i == data->arg.total)
		{
			// TODO print this only at the end of the program only if no deaths?
			//printf("done eatiiin\n");
			*data->phi[0].stop = 2;
			return (ERR);
		}
	}
	return (OK);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		stop = 0;
	// TODO send this to phi cos needed to stop

	if (check_args(argc, argv, &data) == ERR)
	{
		printf("%s\n", ERR_MSG);
		return (1); // ret error? ERR is 0 tho
	}
	if (data.arg.max_eat == 0)
	{
		// TODO maybe [max_eat] could be 0 and just print that each philo eat 0 time(s)?
		printf("philos ate 0\n");
		return (0);
	}
	if (!(data.phi = malloc(sizeof(t_phi) * data.arg.total)))
	{
		// TODO malloc error heres;
		return (0);
	}
	if (init(&data, &stop) == ERR) // TODO add error managment here 
	{
		// init error
		return (0);
	}
	while (phy_loop(&data) == OK);
	usleep(100000);
	//*data.phi[0].stop = 1;
	if (*data.phi[0].stop == 2)
		printf("done eatiiin %d time(s)\n", data.arg.max_eat);
	//while (1);
	return (0);
}
