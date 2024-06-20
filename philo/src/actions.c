/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 08:57:01 by okoca             #+#    #+#             */
/*   Updated: 2024/06/20 09:11:55 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		pl_lock_fork_mutexes(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%lld - %d hold fork!\n", pl_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld - %d hold fork!\n", pl_get_time() - philo->data->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%lld - %d hold fork!\n", pl_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%lld - %d hold fork!\n", pl_get_time() - philo->data->start_time, philo->id);
	}
	return (0);
}

int		pl_unlock_fork_mutexes(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		printf("%lld - %d dropped fork!\n", pl_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld - %d dropped fork!\n", pl_get_time() - philo->data->start_time, philo->id);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld - %d dropped fork!\n", pl_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(philo->left_fork);
		printf("%lld - %d dropped fork!\n", pl_get_time() - philo->data->start_time, philo->id);
	}
	return (0);
}
int		pl_eat_action(t_philo *philo)
{
	pl_lock_fork_mutexes(philo);
	philo->last_eaten = pl_get_time();
	printf("%lld - %d eating\n", pl_get_time() - philo->data->start_time, philo->id);
	usleep(1000 * philo->data->time_to_eat);
	pl_unlock_fork_mutexes(philo);
	return (0);
}

int		pl_sleep_action(t_philo *philo)
{
		printf("%lld - %d sleep!!\n", pl_get_time() - philo->data->start_time, philo->id);
		usleep(1000 * philo->data->time_to_sleep);
		return (0);
}

void	*pl_action(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (i < philo->data->maximum_meal)
	{
		pl_eat_action(philo);
		pl_sleep_action(philo);
		i++;
	}
	return (NULL);
}
