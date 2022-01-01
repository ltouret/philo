/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:45:40 by ltouret           #+#    #+#             */
/*   Updated: 2022/01/01 16:45:42 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	act_time(void)
{
	struct timeval	current_time;
	long int		time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

void	ft_usleep(long int time)
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
