/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:57:47 by ltouret           #+#    #+#             */
/*   Updated: 2022/01/02 18:58:57 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	phi_loop2(t_data *data)
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

static int	phi_loop(t_data *data)
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
