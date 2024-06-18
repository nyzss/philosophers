/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:12:15 by okoca             #+#    #+#             */
/*   Updated: 2024/06/18 20:12:29 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	pl_get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * (long long)1000 + (tv.tv_usec) / 1000);
}
