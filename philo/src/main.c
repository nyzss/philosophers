/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/18 14:17:09 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*task(void *arg)
{
	t_philo	*ctx;

	ctx = (t_philo *)arg;
	pthread_mutex_lock(&(ctx->lock));
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("time: %ld\n", tv.tv_usec);
	usleep(10000);
	printf("hello world!!\n");
	pthread_mutex_unlock(&(ctx->lock));
	return (NULL);
}

void	pl_create_threads(int max)
{
	int			i;
	pthread_t	*f_thread;
	int			p_r;
	t_philo		ctx;

	i = 0;
	if (pthread_mutex_init(&(ctx.lock), NULL) != 0)
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

int main(int ac, char **av)
{
	int	i;
	int	max;

	printf("str1: %s, av[1]: %d\n", av[1], ft_atoi(av[1]));
	if (ac != 2)
	{
		printf("womp womp\n");
		return (1);
	}
	i = 0;
	max = ft_atoi(av[1]);
	pl_create_threads(max);
	printf("hello world!\n");
}