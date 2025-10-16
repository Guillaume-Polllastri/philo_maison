/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:16:08 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/15 16:15:42 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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

void	take_first_fork(t_philo *philo)
{
	if ((philo->id % 2))
		pthread_mutex_lock(&philo->left_fork->mutex);
	else
		pthread_mutex_lock(&philo->right_fork->mutex);
}

void	take_second_fork(t_philo *philo)
{
	if ((philo->id % 2))
		pthread_mutex_lock(&philo->right_fork->mutex);
	else
		pthread_mutex_lock(&philo->left_fork->mutex);
}
