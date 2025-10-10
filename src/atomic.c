/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:53:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/10 13:40:49 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	is_game_running(t_data *data)
{
	int	death_flag;

	pthread_mutex_lock(&data->death_flag_lock);
	death_flag = data->death_flag;
	pthread_mutex_unlock(&data->death_flag_lock);
	return (death_flag == 0);
}

int	try_take_fork(t_philo *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (philo->left_fork->owner == NO_OWNER
		&& philo->right_fork->owner == NO_OWNER)
	{
		philo->left_fork->owner = philo->id;
		printf("%lld %d has taken a fork\n", get_timestamp(), philo->id);
		philo->right_fork->owner = philo->id;
		printf("%lld %d has taken a fork\n", get_timestamp(), philo->id);
		status = 1;
	}
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	return (status);
}

int	release_fork(t_philo *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (philo->left_fork->owner == philo->id
		&& philo->right_fork->owner == philo->id)
	{
		philo->left_fork->owner = NO_OWNER;
		philo->right_fork->owner = NO_OWNER;
		status = 1;
	}
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	return (status);
}
