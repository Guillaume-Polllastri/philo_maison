/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:04:28 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/07 22:51:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

static int	init_philos(t_philo *philos, t_data *data, int *i)
{
	philos[*i].id = *i + 1; 
	philos[*i].nb_meals = 0;
	philos[*i].data = data;
	if (i == 0)
	{
		philos[*i].left_fork = create_fork();
		philos[*i].right_fork = create_fork();
	}
	else if (*i < (data->nb_philos - 1))
	{
		philos[*i].left_fork = create_fork();
		philos[*i].right_fork = philos[*i - 1].left_fork;
	}
	else
	{
		philos[*i].left_fork = philos[0].right_fork;
		philos[*i].right_fork = philos[*i - 1].left_fork;
	}
	if (!philos[*i].left_fork || !philos[*i].right_fork)
		return (0);
	return (1);
}

t_philo	*create_philos(t_data *data)
{
	t_philo	*philos;
	int	i;
	
	philos = malloc(sizeof(*philos) * data->nb_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		if (!init_philos(philos, data, &i))
			return (NULL);
		i++;
	}
	return (philos);
}

static void	*routine_philos(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)(arg);
	printf("Hello my id is: %d\n", philo.id);
	return (NULL);
}

static int	wait_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (1);
}

int	deploy_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = create_philos(data);
	if (!philos)
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine_philos, &philos[i]);
		i++;
	}
	wait_philos(data, philos);
	return (1);
}
