/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:59:09 by ltouret           #+#    #+#             */
/*   Updated: 2022/01/01 17:00:27 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (data->arg.total <= 0 || data->arg.die <= 0 || data->arg.eat <= 0
			|| data->arg.sleep <= 0)
			return (ERR);
	}
	else
		return (ERR);
	return (OK);
}
