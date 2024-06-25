/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:02:59 by okoca             #+#    #+#             */
/*   Updated: 2024/06/25 12:57:33 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_lock_second_part(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		if (philo->data->should_end == 1)
		{
			pl_unlock_fork_mutexes(philo);
			return (1);
		}
		pl_log(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (philo->data->should_end == 1)
		{
			pl_unlock_fork_mutexes(philo);
			return (1);
		}
		pl_log(philo, FORK);
	}
	return (0);
}

int	pl_lock_fork_mutexes(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (philo->data->should_end == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		pl_log(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (philo->data->should_end == 1)
		{
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		pl_log(philo, FORK);
	}
	pl_lock_second_part(philo);
	return (0);
}

int	pl_unlock_fork_mutexes(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}
