/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/18 21:39:46 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*pl_eating(void *arg)
{
	t_ctx			*ctx;

	ctx = (t_ctx *)arg;
	if (ctx->nb_philo % 2 == 0)
	{
		pthread_mutex_lock(&(ctx->));
		usleep(1000 * 100);
		pthread_mutex_unlock(&(ctx->lock_f));
		printf("%lld doing something\n", pl_get_time() - ctx->start_time);
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
		ctx->philosophers[i].left_fork = ctx->forks[i];
		ctx->philosophers[i].right_fork = ctx->forks[(i + 1) % ctx->nb_philo];
		ctx->philosophers[i].last_eaten = pl_get_time();
		if (pthread_create(&(ctx->philosophers[i].thread_id), NULL, pl_eating, ctx) != 0)
			return (1);
		i++;
	}
	return (pl_join_philos(ctx));
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
	int		i;

	i = 0;
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
	// if (pthread_mutex_init(&(ctx.lock_f), NULL) != 0)
	// {
	// 	printf("error when creating mutexes\n");
	// 	return (0);
	// }
	pl_create_philos(&ctx);
	// pthread_mutex_destroy(&(ctx.lock_f));
	printf("hello world!\n");
}
