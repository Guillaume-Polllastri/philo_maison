/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:20:14 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/13 18:07:58 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_philo_status(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->lock);
	if (!philo->death)
		printf("%lld %d %s\n", get_timestamp(), philo->id, s);
	pthread_mutex_unlock(&philo->lock);
}

void	stop_game(t_data *data)
{
	pthread_mutex_lock(&data->stop_flag_lock);
	data->stop_flag = 1;
	pthread_mutex_unlock(&data->stop_flag_lock);
}

void	set_last_meal_time(t_philo *philo, long long time)
{
	pthread_mutex_lock(&philo->lock);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->lock);
}

long long	get_last_meal_time(t_philo *philo)
{
	long long	last_meal_time;
	
	pthread_mutex_lock(&philo->lock);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->lock);
	return (last_meal_time);
}
