/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:23:17 by okoca             #+#    #+#             */
/*   Updated: 2024/06/21 17:39:50 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_log(t_philo *philo, t_action action)
{
	pthread_mutex_lock(&(philo->data->meal_mutex));
	if (philo->data->maximum_meal == 0)
	{
		pthread_mutex_unlock(&(philo->data->meal_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->meal_mutex));
	pthread_mutex_lock(&(philo->data->log_mutex));
	if (action == DIED)
		printf("%lld %d has died\n", pl_get_time() - philo->data->start_time, philo->id);
	else if (action == SLEEP)
		printf("%lld %d is sleeping\n", pl_get_time() - philo->data->start_time, philo->id);
	else if (action == EAT)
		printf("%lld %d is eating\n", pl_get_time() - philo->data->start_time, philo->id);
	else if (action == FORK)
		printf("%lld %d took a fork\n", pl_get_time() - philo->data->start_time, philo->id);
	else if (action == THINK)
		printf("%lld %d is thinking\n", pl_get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&(philo->data->log_mutex));
	return (0);
}
