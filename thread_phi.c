/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_phi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:56:21 by ltouret           #+#    #+#             */
/*   Updated: 2022/01/03 17:58:08 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	status(t_phi *phi, int mov)
{
	long int	time;

	if (*phi->stop > 0)
	{
		pthread_mutex_unlock(phi->rf);
		pthread_mutex_unlock(&phi->lf);
		return (ERR);
	}
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

static int	th_phi1(t_phi *phi)
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
		ft_usleep(phi->arg->eat);
	while (1)
	{
		if (phi->arg->max_eat != -1 && phi->nb_eat >= phi->arg->max_eat)
			break ;
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
