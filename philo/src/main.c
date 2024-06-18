/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/18 14:32:46 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	pl_get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

// void	*task(void *arg)
// {
// 	t_philo			*ctx;
// 	long long		start;
// 	long long		end;

// 	ctx = (t_philo *)arg;
// 	start = pl_get_time();
// 	printf("start: %lld\n", pl_get_time());
// 	pthread_mutex_lock(&(ctx->lock));
// 	usleep(1000 * 1000);
// 	printf("hello world!!\n");
// 	pthread_mutex_unlock(&(ctx->lock));
// 	end = pl_get_time();
// 	printf("end: %lld\n", pl_get_time());
// 	printf("total time elapsed: %lld\n", end - start);
// 	return (NULL);
// }

void	*task(void *arg)
{
	t_philo			*ctx;

	ctx = (t_philo *)arg;
	pthread_mutex_lock(&(ctx->lock));
	usleep(1000 * 1000);
	printf("hello world!!\n");
	pthread_mutex_unlock(&(ctx->lock));
	printf("current_time: %lld\n", ctx->time);
	return (NULL);
}

void	pl_create_threads(t_philo *ctx, int max)
{
	int			i;
	pthread_t	*f_thread;
	int			p_r;

	i = 0;
	if (pthread_mutex_init(&(ctx->lock), NULL) != 0)
	{
		printf("error when creating mutexes\n");
		return ;
	}
	f_thread = malloc(sizeof(pthread_t) * max);
	while (i < max)
	{
		if (pthread_create(f_thread + i, NULL, task, &ctx))
		{
			printf("error occured when creating threads, exiting..\n");
			free(f_thread);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < max)
	{
		p_r = pthread_join(f_thread[i], NULL);
		if (p_r != 0)
		{
			printf("error occured when creating threads, exiting..\n");
			free(f_thread);
			return ;
		}
		i++;
	}
	free(f_thread);
	return ;
}
void	*pl_update_time(void *arg)
{
	t_philo		*ctx;
	long long	now;

	now = pl_get_time();
	ctx = (t_philo *)arg;
	ctx->time = now - ctx->start;
	return (NULL);
}

int main(int ac, char **av)
{
	int			max;
	t_philo		ctx;
	pthread_t	time_thread;

	ctx.start = pl_get_time();
	if (ac != 2)
	{
		printf("womp womp\n");
		return (1);
	}
	pthread_create(&time_thread, NULL, &pl_update_time, &ctx);
	max = ft_atoi(av[1]);
	pl_create_threads(&ctx, max);
	pthread_join(time_thread, NULL);
	printf("hello world!\n");
}