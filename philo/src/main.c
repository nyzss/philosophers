/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 09:00:26 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*pl_eating(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->nb_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d took left fork\n", pl_get_time() - philo->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d took right fork\n", pl_get_time() - philo->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d took right fork\n", pl_get_time() - philo->start_time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d took left fork\n", pl_get_time() - philo->start_time, philo->id);
	}
	// pthread_mutex_unlock(&(ctx->lock_f));
	philo->last_eaten = pl_get_time();
	philo->meal_count += 1;
	usleep(1000 * 100);
	printf("%lld %d is eating\n", pl_get_time() - philo->start_time, philo->id);
	if (philo->nb_philo % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		printf("%lld %d dropped left fork\n", pl_get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %d dropped right fork\n", pl_get_time() - philo->start_time, philo->id);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %d dropped right fork\n", pl_get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->left_fork);
		printf("%lld %d dropped left fork\n", pl_get_time() - philo->start_time, philo->id);
	}
	return (NULL);
}

int	pl_join_philos(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->nb_philo)
	{
		if (pthread_join(ctx->philosophers[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	pl_create_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].id = i;
		philos[i].left_fork = &(ctx->forks[i]);
		philos[i].right_fork = &(ctx->forks[(i + 1) % ctx->nb_philo]);
		philos[i].last_eaten = 0;
		philos[i].nb_philo = ctx->nb_philo;
		philos[i].meal_count = 0;
		philos[i].data = data;
		if (pthread_create(&(ctx->philosophers[i].thread_id), NULL, pl_eating, &(ctx->philosophers[i])) != 0)
			return (1);
		i++;
	}
	return (pl_join_philos(ctx));
}
int		pl_destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&(data->forks[i])) != 0)
			return (1);
		i++;
	}
	return (0);

}

int		pl_init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

t_data	pl_init_data(int ac, char **av)
{
	t_data	data;
	mutex	forks[200];

	if (ac == 6)
		data.maximum_meal = ft_atoi(av[5]);
	data.nb_philo = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	data.start_time = pl_get_time();
	data.forks = forks;
	pl_init_forks(&data);
	return (data);
}

// nb_philo, time_to_die, time_to_eat, time_to_sleep, [max eat]
// 5 800 200 200 7
int main(int ac, char **av)
{
	t_philo		philo[200];
	t_data		data;

	if (pl_parse_args(ac, av) == 1)
		return (1);
	data = pl_init_data(ac, av);
	pl_create_philos(&data, philo);
	pl_destroy_forks(&data);
	printf("hello world!\n");
}
