/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:45:34 by jules             #+#    #+#             */
/*   Updated: 2024/03/26 09:38:46 by jules            ###   ########.fr       */
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
	pthread_mutex_lock(c->forks + ((p->id_philo + 1) % c->nb_philo));
	p->state = 1;
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
	p->state = 2;
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
		print_state(p);
		if (p->state == 0)
			eat(p, p->common);
		else
		{
			p->state = 0;
			wait_ms(p->common, p->common->time_to_sleep);
		}
	}
	return (NULL);
}
