/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:41:40 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/09 14:50:37 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define NO_OWNER 0

typedef struct s_fork
{
	int				owner;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	long long		start_time;
	int				death_flag;
	pthread_mutex_t	death_flag_lock;
	pthread_mutex_t	print;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

int					ft_atoi(char *nptr);
int					*parse_args(char **av);
void				init_data(t_data *data, int *tab);
t_philo				*create_philos(t_data *data);
void				print_philos(t_philo *philos, t_data *data);
int					deploy_philos(t_data *data);
void				destroy_fork_mutex(t_fork *forks, int nb_initialized);
t_fork				*create_fork(void);
int					is_game_running(t_data *data);
int					try_take_fork(t_philo *philo);
int					release_fork(t_philo *philo);
long long			get_timestamp(void);

#endif