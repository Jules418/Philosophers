/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 04:56:49 by jules             #+#    #+#             */
/*   Updated: 2024/04/12 21:18:06 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo p)
{
	if (!p)
		return ;
	pthread_mutex_destroy(&(p->eat_count_mutex));
	pthread_mutex_destroy(&(p->state_mutex));
	pthread_mutex_destroy(&(p->last_time_eat_mutex));
	free(p);
}

void	free_philo_array(t_philo *ps, int size)
{
	int	i;

	if (!ps)
		return ;
	i = 0;
	while (i < size)
	{
		free_philo(ps[i]);
		i++;
	}
	free(ps);
}

t_philo	create_philo(int id, t_common c)
{
	t_philo	p;

	p = malloc(sizeof(struct s_philo));
	if (!p)
		return (NULL);
	p->id_philo = id;
	p->common = c;
	p->eat_count = 0;
	p->eat_count_mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	p->state = 0;
	p->left_fork = c->forks + id;
	p->right_fork = c->forks + (id + 1) % c->nb_philo;
	p->last_time_eat_mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	p->state_mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	return (p);
}

t_philo	*create_philo_array(t_common c)
{
	int		i;
	t_philo	*ps;

	if (!c)
		return (NULL);
	ps = malloc(sizeof(t_philo) * c->nb_philo);
	i = 0;
	while (i < c->nb_philo)
	{
		ps[i] = create_philo(i, c);
		if (!(ps[i]))
			return (free_philo_array(ps, i), NULL);
		i++;
	}
	return (ps);
}

int	print_state(t_philo p)
{
	struct timeval	tv;
	long			dt;
	char			*message;

	if (get_state(p) == POSSES_ONE_FORK)
		message = "has taken a fork";
	else if (get_state(p) == EATING)
		message = "is eating";
	else if (get_state(p) == SLEEPING)
		message = "is sleeping";
	else if (get_state(p) == THINKING)
		message = "is thinking";
	else
		message = "died";
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	dt = time_diff(tv, p->common->start_time);
	if (get_running(p->common) || (get_state(p) == DEAD))
		printf("%ld %d %s\n", dt, p->id_philo + 1, message);
	return (0);
}
