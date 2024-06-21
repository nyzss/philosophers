/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:52:05 by okoca             #+#    #+#             */
/*   Updated: 2024/06/21 08:23:23 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_start_philos(t_data *data)
{
	t_philo	philos[200];

	pl_init_philos(data, philos);
	pl_track_philos(data, philos);
	pl_join_philos(data, philos);
	return (0);
}

int	pl_check_dead(t_data *data, t_philo *philo, int *finished)
{
	// printf("out meal remaining: %d\n", philo->meal_remaining);
	if (philo->last_eaten > data->time_to_die)
		data->should_end = 1;
	if (philo->meal_remaining == 0)
	{
		// printf("meal remaining: %d\n", philo->meal_remaining);
		*finished += 1;
	}
	return (0);
}

int	pl_track_philos( t_data *data, t_philo *philos)
{
	int		i;
	int		j;
	int		finished;

	i = 0;
	while (i < data->maximum_meal + 4)
	{
		finished = 0;
		j = 0;
		pthread_mutex_lock(&(data->log_mutex));
		// printf("data: %d\n", data->should_end);
		// printf("max meal: %d\n", data->maximum_meal);
		while (j < data->nb_philo)
		{
			pl_check_dead(data, philos, &finished);
			j++;
		}
		if (finished == data->nb_philo)
		{
			// printf("######### All philosophers ate! ############\n");
			// printf("print %d\n", finished);
			// printf("nb_philo %d\n", data->nb_philo);
			data->should_end = 1;
		}
		pthread_mutex_unlock(&(data->log_mutex));
		usleep(1000 * data->time_to_eat);
		i++;
	}
	return (0);
}
