/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:34:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/15 12:43:30 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void	destroy_fork_mutex(t_fork *forks, int nb_initialized)
{
	int	i;

	i = 0;
	while (i < nb_initialized)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
	free(forks);
}

void	print_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		printf("Philos (%d):\n", philos[i].id);
		printf("nb_meals (%d)\n", philos[i].nb_meals);
		i++;
	}
}

long long	get_timestamp(void)
{
	long long		res;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	res = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (res);
}

long long	min_value(long long a, long long b)
{
	if (a < b)
		return (a);
	return (b);
}

int	safe_usleep(long long usec)
{
	if (usec <= 0)
		return (0);
	return (usleep(usec));
}
