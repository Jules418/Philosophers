/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:59:42 by jules             #+#    #+#             */
/*   Updated: 2024/03/19 05:13:45 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <limits.h>
# include <pthread.h>

typedef struct s_common
{
	pthread_mutex_t	*forks;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_counter;
}	*t_common;

typedef struct s_philo
{
	int			id_philo;
	int			last_time_eat;
	int			eat_count;
	t_common	common;
}	*t_philo;

int				ft_atoi(char *s, int *err_code);

void			free_forks(pthread_mutex_t *forks, int size);
void			free_common(t_common c);
pthread_mutex_t	*initialize_forks(int nb_philo);
int				errors_in_common(t_common c);
t_common		initialize_common(int argc, char **argv);

void	free_philo(t_philo p);
void	free_philo_array(t_philo *ps, int size);
t_philo	create_philo(int id, t_common c);
t_philo	*create_philo_array(t_common c);

#endif