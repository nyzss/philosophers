/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:39:26 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 11:04:11 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*pl_eating(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pl_lock_forks(philo);
	pl_log_action(philo, EAT);
	pl_unlock_forks(philo);
	return (NULL);
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
		pl_log_action(philo, FORK);
		pthread_mutex_unlock(philo->right_fork);
		pl_log_action(philo, FORK);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pl_log_action(philo, FORK);
		pthread_mutex_unlock(philo->left_fork);
		pl_log_action(philo, FORK);
	}
	return (0);
}