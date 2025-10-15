/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:20:14 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/15 11:38:32 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_philo_status(t_philo *philo, char *s)
{
	int	is_dead;

	is_dead = get_death_status(philo);
	pthread_mutex_lock(&philo->data->print);
	if (!is_dead)
		printf("%lld %d %s\n", get_timestamp(), philo->id, s);
	pthread_mutex_unlock(&philo->data->print);
}

void	stop_game(t_data *data)
{
	pthread_mutex_lock(&data->stop_flag_lock);
	data->stop_flag = 1;
	pthread_mutex_unlock(&data->stop_flag_lock);
}

void	set_last_meal_time(t_philo *philo, long long time)
{
	// printf("set_last_meal_time : %ld\n", pthread_self());
	pthread_mutex_lock(&philo->lock);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->lock);
	// printf("set_last_meal_time unlock: %ld\n", pthread_self());
}

long long	get_last_meal_time(t_philo *philo)
{
	long long	last_meal_time;

	// printf("get_last_meal_time : %ld\n", pthread_self());
	pthread_mutex_lock(&philo->lock);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->lock);
	// printf("get_last_meal_time unlock: %ld\n", pthread_self());
	return (last_meal_time);
}
