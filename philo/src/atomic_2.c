/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:20:14 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/17 11:32:45 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

void	print_philo_status(t_philo *philo, char *s)
{
	int	is_dead;

	if (!is_game_running(philo->data))
		return ;
	is_dead = get_death_status(philo);
	pthread_mutex_lock(&philo->data->print);
	if (!is_dead)
		printf("%lld %d %s\n", get_timestamp() - philo->start_time, philo->id,
			s);
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
	pthread_mutex_lock(&philo->last_meal_time_lock);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->last_meal_time_lock);
}

long long	get_last_meal_time(t_philo *philo)
{
	long long	last_meal_time;

	pthread_mutex_lock(&philo->last_meal_time_lock);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_time_lock);
	return (last_meal_time);
}
