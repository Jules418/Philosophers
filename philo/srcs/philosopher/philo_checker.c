/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:02:37 by jules             #+#    #+#             */
/*   Updated: 2024/04/15 10:49:41 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead_philo(t_philo p)
{
	struct timeval	current_time;
	long			dt;

	if (!should_run(p))
		return (0);
	if (gettimeofday(&current_time, NULL) == -1)
	{
		return (1);
	}
	dt = time_diff(current_time, get_last_time_eat(p));
	return (dt > p->common->time_to_die);
}

void	*dead_checker(void *args)
{
	t_philo		*p;
	t_common	c;
	int			i;

	p = args;
	if (!p)
		return (NULL);
	c = p[0]->common;
	pthread_mutex_lock(&(c->starting_mutex));
	pthread_mutex_unlock(&(c->starting_mutex));
	usleep(1000);
	i = 0;
	while (get_running(c))
	{
		if (is_dead_philo(p[i]))
		{
			set_running(c, 0);
			set_state(p[i], DEAD);
			break ;
		}
		i = (i + 1) % (c->nb_philo);
	}
	if (get_state(p[i]) == DEAD)
		print_state(p[i]);
	return (NULL);
}
