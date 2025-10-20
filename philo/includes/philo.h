/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:41:40 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/20 11:43:10 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

# define NO_OWNER 0
# define STR_MAX_INT "2147483647"
# define STR_MIN_INT "2147483648"

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
	int				stop_flag;
	pthread_mutex_t	stop_flag_lock;
	pthread_mutex_t	print;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long long		last_meal_time;
	pthread_mutex_t	last_meal_time_lock;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	int				death;
	pthread_mutex_t	death_lock;
	long long		start_time;
	t_data			*data;
}					t_philo;

int					ft_positive_atoi(char *nptr);
int					*parse_args(char **av);
void				init_data(t_data *data, int *tab, int tab_len);
t_philo				*create_philos(t_data *data);
void				print_philos(t_philo *philos, t_data *data);
int					deploy_philos(t_data *data);
void				destroy_fork_mutex(t_fork *forks, int nb_initialized);
t_fork				*create_fork(void);
int					is_game_running(t_data *data);
void				release_fork(t_philo *philo);
long long			get_timestamp(void);
long long			min_value(long long a, long long b);
void				set_death_status(t_philo *philo);
int					is_philo_alive(t_philo *philo);
void				*routine_death_handler(void *arg);
void				print_philo_status(t_philo *philo, char *s);
void				stop_game(t_data *data);
bool				take_first_fork(t_philo *philo);
bool				take_second_fork(t_philo *philo);
void				set_last_meal_time(t_philo *philo, long long time);
long long			get_last_meal_time(t_philo *philo);
int					get_death_status(t_philo *philo);
int					get_order(int id, int nb_philos);
int					safe_usleep(long long usec);
long long			get_time_to_think(t_philo *philo, bool is_starting);
void				free_fork(t_philo *philos);
int 				ft_strlen(char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

#endif