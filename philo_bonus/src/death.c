/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:02:48 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/29 14:49:43 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

void	*death_handler(void *arg)
{
	t_philo	*philo;
	t_philo	*head;
	int		status;
	int		i;

	philo = (t_philo *)arg;
	waitpid(philo->pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 42)
	{
		head = (t_philo *)((char *)philo - ((philo->id - 1) * sizeof(t_philo)));
		i = 0;
		while (i < philo->data->nb_philos)
		{
			kill(head[i].pid, SIGTERM);
			i++;
		}
	}
	return (NULL);
}
