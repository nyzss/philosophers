/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:39:26 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 09:41:40 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d took left fork\n", pl_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d took right fork\n", pl_get_time() - philo->data->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d took right fork\n", pl_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d took left fork\n", pl_get_time() - philo->data->start_time, philo->id);
	}
	return (0);
}

int	pl_unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		printf("%lld %d dropped left fork\n", pl_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %d dropped right fork\n", pl_get_time() - philo->data->start_time, philo->id);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %d dropped right fork\n", pl_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(philo->left_fork);
		printf("%lld %d dropped left fork\n", pl_get_time() - philo->data->start_time, philo->id);
	}
	return (0);
}