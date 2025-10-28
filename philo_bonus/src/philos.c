/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:59:53 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/28 19:37:45 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	init_semaphore(t_data *data)
{
	sem_unlink("/forks");
    sem_unlink("/print");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nb_philos);
	data->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
}

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

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_timestamp() - philo->last_meal_time >= philo->data->time_to_die)
		{
			philo->is_dead = true;
			print_philo_status(philo, philo->data, "died");
			exit(42);
		}
		if (philo->data->nb_meals != -1 && philo->nb_meals >= philo->data->nb_meals)
			exit(0xc0ffee);
	}
	return (NULL);
}

static void	routine_philos(t_philo *philo, t_data *data)
{
	bool	is_starting;
	
	is_starting = true;
	pthread_create(&philo->death, NULL, philo_monitor, philo);
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
        philo->last_meal_time = get_timestamp();
        sem_post(data->forks);
        sem_post(data->forks);
		print_philo_status(philo, data, "is sleeping");
		usleep(data->time_to_sleep * 1000);
	}
}

static int	spawn_children(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
            return (0); 
		if (philo[i].pid == 0)
		{
			philo[i].last_meal_time = get_timestamp();
			philo[i].start_time = philo[i].last_meal_time;
			routine_philos(&philo[i], data);
			break ;
		}
		i++;
	}
	return (1);
}

static void	wait_children(t_philo *philo, t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_philos)
	{
		waitpid(philo[i].pid, &status, 0);
		i++;
	}
}

int deploy_philos(t_data *data)
{
	t_philo	*philos;
	int		i;
	pthread_t	reaper;

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
		pthread_create(&reaper, NULL, death_handler, &philos[i]);
		i++;
	}
	wait_children(philos, data);
	free(philos);
	return (1);
}
