/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:59:53 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/29 15:44:51 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static t_philo	*create_philos(t_philo *philo, t_data *data)
{
	int	i;

	philo = malloc(sizeof(*philo) * data->nb_philos);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(*philo) * data->nb_philos);
	i = 0;
	while (i < data->nb_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		i++;
	}
	return (philo);
}

static void	*philo_monitor(void *arg)
{
	t_philo	*philo;
	t_philo	*head;

	philo = (t_philo *)arg;
	head = (t_philo *)((char *)philo - ((philo->id - 1) * sizeof(t_philo)));
	while (1)
	{
		if (get_timestamp() - philo->last_meal_time >= philo->data->time_to_die)
		{
			philo->is_dead = true;
			print_philo_status(philo, philo->data, "died");
			close_semaphore(philo->data);
			free(head);
			exit(42);
		}
		if (philo->data->nb_meals != -1
			&& philo->nb_meals >= philo->data->nb_meals)
		{
			close_semaphore(philo->data);
			free(head);
			exit(0xc0ffee);
		}
	}
	return (NULL);
}

void	routine_philos(t_philo *philo, t_data *data)
{
	bool	is_starting;
	t_philo	*head;

	is_starting = true;
	head = (t_philo *)((char *)philo - ((philo->id - 1) * sizeof(t_philo)));
	if (pthread_create(&philo->death, NULL, philo_monitor, philo))
		return (close_semaphore(data), free(head), exit(42));
	while (1)
	{
		print_philo_status(philo, data, "is thinking");
		usleep(get_time_to_think(philo, data, is_starting));
		is_starting = false;
		sem_wait(data->forks);
		print_philo_status(philo, data, "has taken a fork");
		sem_wait(data->forks);
		print_philo_status(philo, data, "has taken a fork");
		print_philo_status(philo, data, "is eating");
		usleep(data->time_to_eat * 1000);
		philo->nb_meals++;
		philo->last_meal_time = get_timestamp();
		sem_post(data->forks);
		sem_post(data->forks);
		print_philo_status(philo, data, "is sleeping");
		usleep(data->time_to_sleep * 1000);
	}
}

static int	wait_philos(t_philo *philos, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_join(philos[i].reaper, NULL);
		i++;
	}
	return (1);
}

int	deploy_philos(t_data *data)
{
	t_philo		*philos;
	int			i;

	philos = NULL;
	init_semaphore(data);
	philos = create_philos(philos, data);
	if (!philos)
		return (0);
	if (!spawn_children(philos, data))
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&philos[i].reaper, NULL, death_handler, &philos[i]);
		i++;
	}
	wait_philos(philos, i);
	wait_children(philos, data);
	free(philos);
	close_semaphore(data);
	return (1);
}
