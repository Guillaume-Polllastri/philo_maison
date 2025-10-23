/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:59:53 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/23 14:05:49 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <string.h>

static void	init_semaphore(t_data *data)
{
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nb_philos);
	data->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	data->death = sem_open("/death", O_CREAT | O_EXCL, 0644, 0);
}

static void	init_philo(t_data *data)
{
	
}

static int	spawn_forks(t_philo *philo)
{
	int		i;

	philo->pid = malloc(sizeof(*philo->pid) * philo->data->nb_philos);
	if (!philo->pid)
		return (0);
	i = 0;
	while (i < philo->data->nb_philos)
	{
		// philo[i].last_meal_time = get_timestamp();
		// philo[i].start_time = philo[i].last_meal_time;
		philo->pid[i] = fork();
		i++;
	}
	return (1);
}

int deploy_philos(t_data *data)
{
	t_philo	*philo;

	init_semaphore(data);
	if (!spawn_forks(philo))
		return (0);
	return (1);
}
