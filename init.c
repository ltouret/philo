/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:59:09 by ltouret           #+#    #+#             */
/*   Updated: 2022/01/03 17:06:39 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args_digit(int argc, char *argv[])
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
		if (data->arg.total <= 0 || data->arg.die <= 0 || data->arg.eat <= 0
			|| data->arg.sleep <= 0)
			return (ERR);
	}
	else
		return (ERR);
	return (OK);
}

static int	create_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->arg.total)
	{
		if (pthread_create(&data->phi[i].th_id,
				NULL, (void *)th_phi, &data->phi[i]) != 0)
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
