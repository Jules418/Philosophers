/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:52:33 by jules             #+#    #+#             */
/*   Updated: 2024/04/12 19:39:22 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_running(t_common c)
{
	int	value;

	pthread_mutex_lock(&(c->running_mutex));
	value = c->running;
	pthread_mutex_unlock(&(c->running_mutex));
	return (value);	
}

void set_running(t_common c, int value)
{
	pthread_mutex_lock(&(c->running_mutex));
	c->running = value;
	pthread_mutex_unlock(&(c->running_mutex));
}

int	trylock_fork(t_fork *fork, int id_philo)
{
	pthread_mutex_lock(&(fork->mutex));
	if (fork->taken)
	{
		pthread_mutex_unlock(&(fork->mutex));
		return (0);
	}
	fork->taken = 1;
	fork->id_philo = id_philo;
	pthread_mutex_unlock(&(fork->mutex));
	return (1);
}

void	unlock_fork(t_fork *fork, int id_philo)
{
	pthread_mutex_lock(&(fork->mutex));
	if (id_philo == fork->id_philo)
	{
		fork->id_philo = -1;
		fork->taken = 0;
	}
	pthread_mutex_unlock(&(fork->mutex));
}
