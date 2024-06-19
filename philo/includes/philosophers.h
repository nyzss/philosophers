/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:19:46 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 09:02:42 by okoca            ###   ########.fr       */
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

typedef pthread_mutex_t mutex;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				maximum_meal;
	long long		start_time;
	mutex			*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				is_eating;
	int				is_sleeping;
	int				meal_count;
	long long		last_eaten;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		thread_id;
	t_data			*data;
}	t_philo;

int			ft_atoi(const char *str);

long long	pl_get_time(void);

int			pl_parse_args(int ac, char **av);

#endif