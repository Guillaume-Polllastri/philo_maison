/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:51:42 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/06 15:03:46 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) || pthread_mutex_init(&data->death, NULL))
		return (0);
	return (1);
}

static int	init_fork_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (destroy_fork_mutex(data->forks, i), 0);
		i++;
	}
	return (1);
}

static int	init_philos(t_data *data)
{
	int	i;
	
	data->philos = malloc(sizeof(*data->philos) * data->nb_philos);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i;
		data->philos[i].status = 0;
		data->philos[i].nb_meals = 0;
		data->philos[i].thread = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + data->nb_philos - 1) % data->nb_philos];
		i++;
	}
	return (1);
}

int	setup_data(t_data *data, int *tab)
{
	data->nb_philos = tab[0];
	data->time_to_die = tab[1];
	data->time_to_eat = tab[2];
	data->time_to_sleep = tab[3];
	if (tab[4])
		data->nb_meals = tab[4];
	if (!init_mutex(data))
		return (0);
	if (!init_fork_mutex(data))
		return (0);
	if (!init_philos(data))
		return (0);
	return (1);
}
