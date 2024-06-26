/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:19:46 by okoca             #+#    #+#             */
/*   Updated: 2024/06/24 09:10:51 by okoca            ###   ########.fr       */
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

# define DEATH 1
# define SATIATED 2

typedef pthread_mutex_t	t_mutex;
typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
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
	int				end_reason;
	t_mutex			log_mutex;
	t_mutex			end_mutex;
	t_mutex			forks[200];
}	t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				meal_remaining;
	long long		last_eaten;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
	t_mutex			meal_mutex;
	pthread_t		thread_id;
	t_data			*data;
}	t_philo;

int			ft_atoi(const char *str);

long long	pl_get_time(void);

int			pl_parse_args(int ac, char **av);

int			pl_init_data(t_data *data, int ac, char **av);

int			pl_init_mutexes(t_data *data);

int			pl_destroy_mutexes(t_data *data);

int			pl_start_philos(t_data *data);

int			pl_init_philos(t_data *data, t_philo *philos);

int			pl_join_philos(t_data *data, t_philo *philos);

int			pl_handle_single_philo(t_data *data);

void		*pl_action(void *arg);

int			pl_eat_action(t_philo *philo);

int			pl_track_philos( t_data *data, t_philo *philos);

int			pl_log(t_philo *philo, t_action action);

int			pl_end_check(t_philo *philo);

int			pl_lock_fork_mutexes(t_philo *philo);

int			pl_unlock_fork_mutexes(t_philo *philo);

int			ft_sleep(t_data *data, int time);

#endif