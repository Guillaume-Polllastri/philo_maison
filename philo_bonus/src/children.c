/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:31:28 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/29 13:33:00 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/wait.h>

int	spawn_children(t_philo *philo, t_data *data)
{
	int	i;

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

void	wait_children(t_philo *philo, t_data *data)
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
