/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:44:28 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 11:00:16 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_log_action(t_philo *philo, t_action action)
{
	pthread_mutex_lock(&(philo->data->log_mutex));
	if (action == FORK)
	{
		printf("%lld %d has taken a fork\n", pl_get_time() - philo->data->start_time, philo->id);
	}
	else if (action == EAT)
	{
		philo->last_eaten = pl_get_time();
		philo->meal_count += 1;
		printf("%lld %d is eating\n", pl_get_time() - philo->data->start_time, philo->id);
		usleep(1000 * philo->data->time_to_eat);
	}
	pthread_mutex_unlock(&(philo->data->log_mutex));
	return (0);
}

// timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died