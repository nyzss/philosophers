/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:39:26 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 14:28:49 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_eating(t_philo *philo)
{
	pl_lock_forks(philo);
	pthread_mutex_lock(&(philo->data->log_mutex));
	philo->last_eaten = pl_get_time();
	philo->meal_remaining -= 1;
	pthread_mutex_unlock(&(philo->data->log_mutex));
	pl_log_action(philo, EAT);
	usleep(1000 * philo->data->time_to_eat);
	pl_unlock_forks(philo);
	return (0);
}

int	pl_lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pl_log_action(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		pl_log_action(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pl_log_action(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		pl_log_action(philo, FORK);
	}
	return (0);
}

int	pl_unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pl_log_action(philo, DROP);
		pthread_mutex_unlock(philo->right_fork);
		pl_log_action(philo, DROP);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pl_log_action(philo, DROP);
		pthread_mutex_unlock(philo->left_fork);
		pl_log_action(philo, DROP);
	}
	return (0);
}