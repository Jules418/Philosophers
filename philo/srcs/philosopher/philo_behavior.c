/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:45:34 by jules             #+#    #+#             */
/*   Updated: 2024/04/12 10:56:32 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_ms(t_common c, int ms)
{
	struct timeval	start_time;
	struct timeval	current_time;
	long			dt;

	dt = 0;
	if (gettimeofday(&start_time, NULL) == -1)
		return ;
	while (c->running && (dt < ms))
	{
		usleep(500);
		if (gettimeofday(&current_time, NULL) == -1)
			return ;
		dt = time_diff(current_time, start_time);
	}
	return ;
}

int	should_run(t_philo p)
{
	if (p->common->max_eat_counter < 0)
		return (p->common->running);
	if (p->eat_count + 1 > p->common->max_eat_counter)
		return (0);
	return (p->common->running);
}

void	eat(t_philo p, t_common c)
{
	if (!should_run(p))
		return ;
	pthread_mutex_lock(c->forks + p->id_philo);
	p->state = POSSES_ONE_FORK;
	print_state(p);
	if (((p->id_philo + 1) % c->nb_philo) != p->id_philo)
		pthread_mutex_lock(c->forks + ((p->id_philo + 1) % c->nb_philo));
	else
	{
		pthread_mutex_unlock(c->forks + p->id_philo);
		wait_ms(p->common, p->common->time_to_die * 2);
	}
	p->state = EATING;
	p->eat_count++;
	if (gettimeofday(&(p->last_time_eat), NULL) == -1)
		c->running = 0;
	else
	{
		print_state(p);
		wait_ms(c, c->time_to_eat);
	}
	pthread_mutex_unlock(c->forks + p->id_philo);
	pthread_mutex_unlock(c->forks + ((p->id_philo + 1) % c->nb_philo));
}

void	*routine_philo(void *arg)
{
	t_philo	p;

	p = arg;
	if (gettimeofday(&(p->last_time_eat), NULL) == -1)
	{
		p->common->running = 0;
		return (NULL);
	}
	if (p->id_philo % 2)
		wait_ms(p->common, 100);
	while (should_run(p))
	{
		p->common->running = !print_state(p);
		if (p->state == THINKING)
			eat(p, p->common);
		else
		{
			p->state = SLEEPING;
			wait_ms(p->common, p->common->time_to_sleep);
			p->state = THINKING;
		}
	}
	return (NULL);
}
