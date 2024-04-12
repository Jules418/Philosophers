/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:02:37 by jules             #+#    #+#             */
/*   Updated: 2024/04/12 10:46:27 by jbanacze         ###   ########.fr       */
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
	dt = time_diff(current_time, p->last_time_eat);
	return (dt > p->common->time_to_die);
}

void	*dead_checker(void *args)
{
	t_philo	*p;
	int		*running;
	int		i;

	p = args;
	if (!p)
		return (NULL);
	running = &(p[0]->common->running);
	i = 0;
	while (*running)
	{
		if (is_dead_philo(p[i]))
		{
			*running = 0;
			p[i]->state = DEAD;
			break ;
		}
		i = (i + 1) % (p[0]->common->nb_philo);
	}
	if (p[i]->state == DEAD)
		print_state(p[i]);
	return (NULL);
}
