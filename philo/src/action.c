/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:44:28 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 12:21:17 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_sleep(t_philo *philo)
{
	pl_log_action(philo, SLEEP);
	usleep(1000 * philo->data->time_to_sleep);
	return (0);
}

void	*pl_action(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// pthread_mutex_lock(&(philo->data->log_mutex));
		if (pl_get_time() - philo->last_eaten > philo->data->time_to_die)
		{
			pl_log_action(philo, DIED);
			// pthread_mutex_unlock(&(philo->data->log_mutex));
			break ;
		}
		// pthread_mutex_unlock(&(philo->data->log_mutex));
		pl_eating(philo);
		pl_eating(philo);
		pl_sleep(philo);
		pl_log_action(philo, THINK);
	}
	printf("hello\n\n");
	return (NULL);
}

int	pl_log_action(t_philo *philo, t_action action)
{
	pthread_mutex_lock(&(philo->data->log_mutex));
	if (action == FORK)
		printf("%lld %d has taken a fork\n", pl_get_time() - philo->data->start_time, philo->id);
	else if (action == DROP)
		printf("%lld %d has dropped a fork\n", pl_get_time() - philo->data->start_time, philo->id);
	else if (action == THINK)
		printf("%lld %d is thinking\n", pl_get_time() - philo->data->start_time, philo->id);
	else if (action == THINK)
		printf("%lld %d is thinking\n", pl_get_time() - philo->data->start_time, philo->id);
	else if (action == EAT)
		printf("%lld %d is eating\n", pl_get_time() - philo->data->start_time, philo->id);
	else if (action == DIED)
		printf("%lld %d has died\n", pl_get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&(philo->data->log_mutex));
	return (0);
}

// timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died