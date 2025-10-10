/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:04:28 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/10 14:46:04 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	init_philos(t_philo *philos, t_data *data, int *i)
{
	philos[*i].id = *i + 1;
	philos[*i].nb_meals = 0;
	philos[*i].data = data;
	if (*i == 0)
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
	int		i;

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
	t_philo		*philo;
	int			status;
	long long	start_time;

	philo = (t_philo *)(arg);
	status = 1;
	start_time = get_timestamp();
	printf("%lld %d is thinking\n", get_timestamp(), philo->id);
	while (status && is_game_running(philo->data))
	{
		if (try_take_fork(philo))
		{
			printf("%lld %d is eating\n", get_timestamp(), philo->id);
			philo->nb_meals++;
			usleep(philo->data->time_to_eat * 1000);
		}
		if (release_fork(philo))
		{
			printf("%lld %d is sleeping\n", get_timestamp(), philo->id);
			usleep(philo->data->time_to_sleep * 1000);
			printf("%lld %d is thinking\n", get_timestamp(), philo->id);
		}
		if (get_timestamp() - start_time >= philo->data->time_to_die)
		{
			philo->data->death_flag = 1;
			printf("%lld %d died\n", get_timestamp(), philo->id);
		}
		if (philo->nb_meals == philo->data->nb_meals
			&& !philo->data->death_flag)
			status = 0;
	}
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
	if (!data->death_flag)
		printf("🎉 Tous les philosophes sont partis de table\n");
	return (1);
}
