/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:19:46 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 16:24:27 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

typedef pthread_mutex_t mutex;

typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
	DROP,
	SATISFIED,
}	t_action;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				maximum_meal;
	long long		start_time;
	int				should_end;
	mutex			log_mutex;
	mutex			forks[200];
}	t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				meal_remaining;
	long long		last_eaten;
	mutex			*right_fork;
	mutex			*left_fork;
	pthread_t		thread_id;
	t_data			*data;
}	t_philo;

int			ft_atoi(const char *str);

long long	pl_get_time(void);

int			pl_parse_args(int ac, char **av);

int			pl_lock_forks(t_philo *philo);

int			pl_unlock_forks(t_philo *philo);

int			pl_eating(t_philo *philo);

int			pl_log_action(t_philo *philo, t_action action);

void		*pl_action(void *arg);

int			pl_init_data(t_data *data, int ac, char **av);

int			pl_init_mutexes(t_data *data);

int			pl_destroy_mutexes(t_data *data);

int			pl_start_philos(t_data *data);

int			pl_init_philos(t_data *data, t_philo *philos);

int			pl_join_philos(t_data *data, t_philo *philos);

#endif
