/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:19:46 by okoca             #+#    #+#             */
/*   Updated: 2024/06/18 20:07:29 by okoca            ###   ########.fr       */
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

typedef struct s_philo
{
	int			id;
	int			dead;
	int			is_eating;
	int			is_sleeping;
	pthread_t	thread_id;
}	t_philo;

typedef struct s_ctx
{
	int				nb_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				max_eat;
	t_philo			philosophers[200];
	pthread_mutex_t	lock_f;
	long	long	start_time;
	int				meal_count;
}	t_ctx;

int		ft_atoi(const char *str);

#endif