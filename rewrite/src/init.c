/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:37:43 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 15:41:20 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_init_data(t_data *data, int ac, char **av)
{
	t_data	new;

	new.nb_philo = av[1];
	new.time_to_die = av[2];
	new.time_to_die = av[3];
	new.time_to_sleep = av[4];
	new.maximum_meal = 0;
	if (ac == 6)
		new.maximum_meal = av[5];
	*data = new;
	return (0);
}

int	pl_init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (0);
		i++;
	}
	return (0);
}

int	pl_destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&(data->forks[i])) != 0)
			return (0);
		i++;
	}
	return (0);
}
