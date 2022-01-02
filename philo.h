/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:48:48 by ltouret           #+#    #+#             */
/*   Updated: 2022/01/02 18:40:46 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERR_ARG "Error : Invalid Arguments"
# define ERR_MAL "Error : Malloc"
# define ERR_INI "Error : Init"
# define ATE_ZERO "Done eating 0 meal(s)"
# define ERR 0
# define OK 1

typedef struct s_arg
{
	int			total;
	int			die;
	int			eat;
	int			sleep;
	int			max_eat;
	long int	start_t;
}				t_arg;

typedef struct s_phi
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

typedef struct s_data
{
	t_arg	arg;
	t_phi	*phi;
}				t_data;

long int	act_time(void);
void		ft_usleep(long int time);
int			slen(char *s);
long		ft_atol(char *s);
int			check_args_digit(int argc, char *argv[]);
int			check_args(int argc, char *argv[], t_data *data);

#endif
