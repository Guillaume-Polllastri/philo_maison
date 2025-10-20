/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:56:11 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/20 17:00:55 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define STR_MAX_INT "2147483647"
# define STR_MIN_INT "2147483648"

# include <pthread.h>
# include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
    sem_t           *forks;    
    sem_t           *print;    
    sem_t           *death;    
}					t_data;

typedef struct s_philo
{
	int				nb_meals;
	long long		last_meal_time;
}                   t_philo;

int	    *parse_args(char **av);
int     ft_strlen(char *s);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	init_data(t_data *data, int *tab, int tab_len);

#endif 