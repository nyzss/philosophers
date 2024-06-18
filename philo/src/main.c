/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/18 22:05:53 by okoca            ###   ########.fr       */
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
	usleep(1000 * 500);
	printf("%lld %d is eating\n", pl_get_time() - philo->start_time, philo->id);
	if (philo->nb_philo % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		printf("%lld %d drooped left fork\n", pl_get_time() - philo->start_time, philo->id);
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

int	pl_create_philos(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->nb_philo)
	{
		ctx->philosophers[i].id = i;
		ctx->philosophers[i].left_fork = &(ctx->forks[i]);
		ctx->philosophers[i].right_fork = &(ctx->forks[(i + 1) % ctx->nb_philo]);
		ctx->philosophers[i].last_eaten = 0;
		ctx->philosophers[i].start_time = ctx->start_time;
		ctx->philosophers[i].nb_philo = ctx->nb_philo;
		ctx->philosophers[i].meal_count = 0;
		if (pthread_create(&(ctx->philosophers[i].thread_id), NULL, pl_eating, &(ctx->philosophers[i])) != 0)
			return (1);
		i++;
	}
	return (pl_join_philos(ctx));
}
int		pl_destroy_forks(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->nb_philo)
	{
		if (pthread_mutex_destroy(&(ctx->forks[i])) != 0)
			return (1);
		i++;
	}
	return (0);

}

int		pl_init_forks(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->nb_philo)
	{
		if (pthread_mutex_init(&(ctx->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

t_ctx	pl_init(int ac, char **av)
{
	t_ctx	ctx;

	if (ac == 6)
		ctx.max_eat = ft_atoi(av[5]);
	ctx.nb_philo = ft_atoi(av[1]);
	ctx.time_to_die = ft_atoi(av[2]);
	ctx.time_to_eat = ft_atoi(av[3]);
	ctx.time_to_sleep = ft_atoi(av[4]);
	ctx.start_time = pl_get_time();
	return (ctx);
}

// nb_philo, time_to_die, time_to_eat, time_to_sleep, [max eat]
// 5 800 200 200 7
int main(int ac, char **av)
{
	t_ctx		ctx;

	if (pl_parse_args(ac, av) == 1)
		return (1);
	ctx = pl_init(ac, av);
	pl_init_forks(&ctx);
	pl_create_philos(&ctx);
	pl_destroy_forks(&ctx);
	printf("hello world!\n");
}
