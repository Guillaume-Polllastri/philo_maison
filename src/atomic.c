/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:53:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/16 13:45:51 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <sys/time.h>

int	is_game_running(t_data *data)
{
	int	stop_flag;

	pthread_mutex_lock(&data->stop_flag_lock);
	stop_flag = data->stop_flag;
	pthread_mutex_unlock(&data->stop_flag_lock);
	return (stop_flag == 0);
}

void	release_fork(t_philo *philo)
{
	if (philo->right_fork)
		pthread_mutex_unlock(&philo->right_fork->mutex);
	if (philo->left_fork)
		pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	set_death_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_lock);
	philo->death = 1;
	pthread_mutex_unlock(&philo->death_lock);
}

int	get_death_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->death_lock);
	status = philo->death;
	pthread_mutex_unlock(&philo->death_lock);
	return (status);
}

int	is_philo_alive(t_philo *philo)
{
	return (!get_death_status(philo));
}
