/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:52:05 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 16:41:00 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*pl_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("LOCKED: left fork, first mutex lock here\n");
		pthread_mutex_lock(philo->right_fork);
		printf("LOCKED: right fork, second mutex lock here\n");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("LOCKED: right fork, THIS IS ODD NUMBERS\n");
		pthread_mutex_lock(philo->left_fork);
		printf("LOCKED: left fork, ODD NUMBERS AGAIN\n");
	}
	printf("%lld - this should happen only once per thread\n", pl_get_time() - philo->data->start_time);
	usleep(1000 * 500);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		printf("UNLOCKED: left fork, first mutex unlock here\n");
		pthread_mutex_unlock(philo->right_fork);
		printf("UNLOCKED: right fork, second mutex unlock here\n");
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		printf("UNLOCKED: right fork, THIS IS ODD NUMBERS AGAIn\n");
		pthread_mutex_unlock(philo->left_fork);
		printf("UNLOCKED: left fork, ODD NUMBERS AGAIN AGAIN\n");
	}
	return (NULL);
}

int	pl_start_philos(t_data *data)
{
	t_philo	philos[200];

	pl_init_philos(data, philos);
	pl_join_philos(data, philos);
	return (0);
}