/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:36:19 by jules             #+#    #+#             */
/*   Updated: 2024/04/12 21:22:24 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				get_state(t_philo p)
{
	int	value;

	pthread_mutex_lock(&(p->state_mutex));
	value = p->state;
	pthread_mutex_unlock(&(p->state_mutex));
	return (value);	
}

void			set_state(t_philo p, int value)
{
	pthread_mutex_lock(&(p->state_mutex));
	p->state = value;
	pthread_mutex_unlock(&(p->state_mutex));
}
int				update_last_time_eat(t_philo p)
{
	int	return_value;

	return_value = 1;
	pthread_mutex_lock(&(p->state_mutex));
	if (gettimeofday((&(p->last_time_eat)), NULL) == -1)
		return_value = 0;
	pthread_mutex_unlock(&(p->state_mutex));
	return (return_value);
}

struct timeval	get_last_time_eat(t_philo p)
{
	struct timeval	tv;
	
	pthread_mutex_lock(&(p->state_mutex));
	tv = p->last_time_eat;
	pthread_mutex_unlock(&(p->state_mutex));
	return (tv);
}

int	incr_eat_counter(t_philo p, int amount)
{
	int	value;
	
	pthread_mutex_lock(&(p->eat_count_mutex));
	p->eat_count += amount;
	value = p->eat_count;
	pthread_mutex_unlock(&(p->eat_count_mutex));
	return (value);
}