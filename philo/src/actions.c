/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 08:57:01 by okoca             #+#    #+#             */
/*   Updated: 2024/06/21 14:07:52 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		pl_lock_fork_mutexes(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pl_log(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pl_log(philo, FORK);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pl_log(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pl_log(philo, FORK);
	}
	return (0);
}

int		pl_unlock_fork_mutexes(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (0);
}

int		pl_sleep_action(t_philo *philo)
{
		pl_log(philo, SLEEP);
		usleep(1000 * philo->data->time_to_sleep);
		return (0);
}

int		pl_think_action(t_philo *philo)
{
		pl_log(philo, THINK);
		return (0);
}

int		pl_eat_action(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(500);
	pl_lock_fork_mutexes(philo);
	pl_log(philo, EAT);
	pthread_mutex_lock(&(philo->data->meal_mutex));
	philo->last_eaten = pl_get_time();
	pthread_mutex_unlock(&(philo->data->meal_mutex));
	usleep(1000 * philo->data->time_to_eat);
	pthread_mutex_lock(&(philo->data->meal_mutex));
	philo->meal_remaining -= 1;
	pthread_mutex_unlock(&(philo->data->meal_mutex));
	pl_unlock_fork_mutexes(philo);
	return (0);
}

void	*pl_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->data->end_mutex));
		if (philo->data->should_end == 1)
		{
			pthread_mutex_unlock(&(philo->data->end_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->end_mutex));
		pl_eat_action(philo);
		pthread_mutex_lock(&(philo->data->end_mutex));
		if (philo->data->should_end == 1)
		{
			pthread_mutex_unlock(&(philo->data->end_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->end_mutex));
		pl_sleep_action(philo);
		pthread_mutex_lock(&(philo->data->end_mutex));
		if (philo->data->should_end == 1)
		{
			pthread_mutex_unlock(&(philo->data->end_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->end_mutex));
		pl_think_action(philo);
	}
	return (NULL);
}
