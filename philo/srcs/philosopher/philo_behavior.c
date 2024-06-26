/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:45:34 by jules             #+#    #+#             */
/*   Updated: 2024/04/15 19:23:24 by jules            ###   ########.fr       */
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
	while (get_running(c) && (dt < ms))
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
		return (get_running(p->common));
	if (incr_eat_counter(p, 0) + 1 > p->common->max_eat_counter)
		return (0);
	return (get_running(p->common));
}

void	eat(t_philo p, t_common c)
{
	if (!should_run(p))
		return ;
	while (should_run(p))
		if (trylock_fork(p->left_fork, p->id_philo))
			break ;
	set_state(p, POSSES_ONE_FORK);
	print_state(p);
	while (should_run(p))
		if (trylock_fork(p->right_fork, p->id_philo))
			break ;
	if (should_run(p))
	{
		print_state(p);
		set_state(p, EATING);
		incr_eat_counter(p, 1);
		if (update_last_time_eat(p) == 0)
			set_running(c, 0);
		else
		{
			print_state(p);
			wait_ms(c, c->time_to_eat);
		}
	}
	unlock_fork(p->right_fork, p->id_philo);
	unlock_fork(p->left_fork, p->id_philo);
}

void	*routine_philo(void *arg)
{
	t_philo	p;

	p = arg;
	pthread_mutex_lock(&(p->common->starting_mutex));
	pthread_mutex_unlock(&(p->common->starting_mutex));
	set_running(p->common, update_last_time_eat(p));
	if (p->id_philo % 2)
		wait_ms(p->common, p->common->time_to_eat / 2);
	while (should_run(p))
	{
		if (get_state(p) == THINKING)
			eat(p, p->common);
		else
		{
			set_state(p, SLEEPING);
			print_state(p);
			wait_ms(p->common, p->common->time_to_sleep);
			set_state(p, THINKING);
			print_state(p);
		}
	}
	return (NULL);
}
