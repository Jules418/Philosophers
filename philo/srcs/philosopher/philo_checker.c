/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:02:37 by jules             #+#    #+#             */
/*   Updated: 2024/03/26 09:40:56 by jules            ###   ########.fr       */
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
		return (1);
	dt = time_diff(current_time, p->last_time_eat);
	return (dt > p->common->time_to_die);
}

void	*dead_checker(void *args)
{
	t_philo	*p;
	int		nb_philo;
	int		*running;
	int		i;
	int		one_died;

	p = args;
	one_died = 0;
	if (!p)
		return (NULL);
	running = &(p[0]->common->running);
	nb_philo = p[0]->common->nb_philo;
	i = 0;
	while (*running)
	{
		if (is_dead_philo(p[i]))
		{
			*running = 0;
			one_died = 1;
			break ;
		}
		i = (i + 1) % nb_philo;
	}
	usleep(500);
	if (one_died)
		printf("philo %d is dead\n", i + 1);
	return (NULL);
}
