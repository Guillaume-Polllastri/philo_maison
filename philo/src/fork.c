/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:16:08 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/16 16:17:25 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>

t_fork	*create_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(*fork));
	if (!fork)
		return (NULL);
	fork->owner = 0;
	pthread_mutex_init(&fork->mutex, NULL);
	return (fork);
}

bool	take_first_fork(t_philo *philo)
{
	if ((philo->id % 2))
	{
		if (philo->left_fork)
		{
			pthread_mutex_lock(&philo->left_fork->mutex);
			print_philo_status(philo, "has taken a fork");
			return (true);
		}
	}
	else
	{
		if (philo->right_fork)
		{
			pthread_mutex_lock(&philo->right_fork->mutex);
			print_philo_status(philo, "has taken a fork");
			return (true);
		}
	}
	return (false);
}

bool	take_second_fork(t_philo *philo)
{
	if ((philo->id % 2))
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_philo_status(philo, "has taken a fork");
		return (true);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_philo_status(philo, "has taken a fork");
		return (true);
	}
	return (false);
}

void	free_fork(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		free(philos[i].right_fork);
		i++;
	}
}
