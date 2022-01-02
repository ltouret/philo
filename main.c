#include "philo.h"

int	status(t_phi *phi, int mov)
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

int	th_phi1(t_phi *phi)
{
	pthread_mutex_unlock(phi->rf);
	pthread_mutex_unlock(&phi->lf);
	if (status(phi, 3) == ERR)
		return (ERR);
	ft_usleep(phi->arg->sleep);
	if (status(phi, 4) == ERR)
		return (ERR);
	return (OK);
}

void	*th_phi(t_phi *phi)
{
	if (phi->nb % 2 == 1)
		ft_usleep(phi->arg->eat / 10);
	while (1)
	{
		if (phi->arg->max_eat != -1 && phi->nb_eat >= phi->arg->max_eat)
			continue ;
		pthread_mutex_lock(&phi->lf);
		if (status(phi, 1) == ERR)
			break ;
		pthread_mutex_lock(phi->rf);
		if (status(phi, 1) == ERR)
			break ;
		if (status(phi, 2) == ERR)
			break ;
		phi->nb_eat++;
		ft_usleep(phi->arg->eat);
		phi->ms_eat = act_time();
		if (th_phi1(phi) == ERR)
			break ;
	}
	return (NULL);
}

int	create_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->arg.total)
	{
		if (pthread_create(&data->phi[i].th_id,
				NULL, (void *)th_phi, &data->phi[i]))
			return (ERR);
	}
	return (OK);
}

int	init(t_data *data, int *stop)
{
	int	i;

	i = -1;
	data->arg.start_t = act_time();
	while (++i < data->arg.total)
	{
		data->phi[i].nb = i ;
		data->phi[i].ms_eat = data->arg.start_t;
		data->phi[i].nb_eat = 0;
		data->phi[i].rf = NULL;
		data->phi[i].stop = stop;
		data->phi[i].arg = &data->arg;
		if (pthread_mutex_init(&(data->phi[i].lf), NULL))
			return (ERR);
		if (data->arg.total == 1)
			return (OK);
		if (i == data->arg.total - 1)
			data->phi[i].rf = &data->phi[0].lf;
		else
			data->phi[i].rf = &data->phi[i + 1].lf;
	}
	if (create_thread(data) == ERR)
		return (ERR);
	return (OK);
}

int	phi_loop2(t_data *data)
{
	int	i;

	if (data->arg.max_eat != -1)
	{
		i = 0;
		while (i < data->arg.total)
		{
			if (data->phi[i].nb_eat < data->arg.max_eat)
				break ;
			i++;
		}
		if (i == data->arg.total)
		{
			*data->phi[0].stop = 2;
			return (ERR);
		}
	}
	return (OK);
}

int	phi_loop(t_data *data)
{
	int			i;
	long int	time;

	i = 0;
	time = act_time();
	while (i < data->arg.total)
	{
		if (time - data->phi[i].ms_eat >= data->arg.die)
		{
			*data->phi[0].stop = 1;
			printf("%ld %d died\n",
				time - data->arg.start_t, data->phi[i].nb + 1);
			return (ERR);
		}
		i++;
	}
	if (phi_loop2(data) == ERR)
		return (ERR);
	return (OK);
}

int	print_exit(char *s, int err)
{
	if (s)
		printf("%s\n", s);
	return (err);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		stop;

	stop = 0;
	if (check_args(argc, argv, &data) == ERR)
		return (print_exit(ERR_ARG, 1));
	if (data.arg.max_eat == 0)
		return (print_exit(ATE_ZERO, 0));
	data.phi = malloc(sizeof(t_phi) * data.arg.total);
	if (!data.phi)
		return (print_exit(ERR_MAL, 2));
	if (init(&data, &stop) == ERR)
		return (print_exit(ERR_INI, 3));
	while (phi_loop(&data) == OK)
		;
	usleep(100000);
	if (*data.phi[0].stop == 2)
		printf("Done eating %d meal(s)\n", data.arg.max_eat);
	return (0);
}
