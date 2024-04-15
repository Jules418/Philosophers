/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:59:42 by jules             #+#    #+#             */
/*   Updated: 2024/04/15 10:55:15 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

# define THINKING 0
# define POSSES_ONE_FORK 1
# define EATING 2
# define SLEEPING 3
# define DEAD 4

typedef struct s_fork
{
	int				taken;
	int				id_philo;
	pthread_mutex_t	mutex;
}	t_fork;
typedef struct s_common
{
	t_fork			*forks;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_counter;
	struct timeval	start_time;
	int				running;
	pthread_mutex_t	running_mutex;
	pthread_mutex_t	starting_mutex;
	pthread_mutex_t	printf_mutex;
}	*t_common;

typedef struct s_philo
{
	int				id_philo;
	struct timeval	last_time_eat;
	pthread_mutex_t	last_time_eat_mutex;
	int				eat_count;
	pthread_mutex_t	eat_count_mutex;
	short			state;
	pthread_mutex_t	state_mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_common		common;
}	*t_philo;

int				ft_atoi(char *s, int *err_code);
long			time_diff(struct timeval a, struct timeval b);

int				get_running(t_common c);
void			set_running(t_common c, int value);

int				trylock_fork(t_fork *fork, int id_philo);
void			unlock_fork(t_fork *fork, int id_philo);

void			free_forks(t_fork *forks, int size);
void			free_common(t_common c);
t_fork			*initialize_forks(int nb_philo);
int				errors_in_common(t_common c);
t_common		initialize_common(int argc, char **argv);

int				get_state(t_philo p);
void			set_state(t_philo p, int value);
int				update_last_time_eat(t_philo p);
struct timeval	get_last_time_eat(t_philo p);
int				incr_eat_counter(t_philo p, int amount);

void			free_philo(t_philo p);
void			free_philo_array(t_philo *ps, int size);
t_philo			create_philo(int id, t_common c);
t_philo			*create_philo_array(t_common c);
int				print_state(t_philo p);
int				should_run(t_philo p);
void			*dead_checker(void *args);
void			*routine_philo(void *arg);

#endif