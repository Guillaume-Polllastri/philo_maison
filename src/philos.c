/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:04:28 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/16 11:53:50 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int	init_philos(t_philo *philos, t_data *data, int *i)
{
	philos[*i].id = *i + 1;
	philos[*i].nb_meals = 0;
	philos[*i].data = data;
	philos[*i].right_fork = create_fork();
	if (*i > 0)
		philos[*i].left_fork = philos[*i - 1].right_fork;
	if (*i > 0 && *i == data->nb_philos - 1)
		philos[0].left_fork = philos[*i].right_fork;
	if (!philos[*i].right_fork)
		return (0);
	pthread_mutex_init(&philos[*i].last_meal_time_lock, NULL);
	pthread_mutex_init(&philos[*i].death_lock, NULL);
	return (1);
}

t_philo	*create_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(*philos) * data->nb_philos);
	if (!philos)
		return (NULL);
	memset(philos, 0, sizeof(*philos) * data->nb_philos);
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
	bool		is_starting;

	is_starting = true;
	philo = (t_philo *)(arg);
	while (is_philo_alive(philo) && is_game_running(philo->data))
	{
		print_philo_status(philo, "is thinking");
		safe_usleep(get_time_to_think(philo, is_starting));
		is_starting = false;
		take_first_fork(philo);
		print_philo_status(philo, "has taken a fork");
		take_second_fork(philo);
		print_philo_status(philo, "has taken a fork");
		set_last_meal_time(philo, get_timestamp());
		print_philo_status(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		release_fork(philo);
		philo->nb_meals++;
		if (philo->data->nb_meals != -1 && philo->nb_meals >= philo->data->nb_meals)
			break ;
		print_philo_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	set_death_status(philo);
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
	t_philo		*philos;
	pthread_t	death_handler;
	int			i;

	philos = create_philos(data);
	if (!philos)
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i].last_meal_time = get_timestamp();
		pthread_create(&philos[i].thread, NULL, routine_philos, &philos[i]);
		i++;
	}
	pthread_create(&death_handler, NULL, routine_death_handler, philos);
	wait_philos(data, philos);
	pthread_join(death_handler, NULL);
	return (1);
}
