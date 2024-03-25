/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 04:56:49 by jules             #+#    #+#             */
/*   Updated: 2024/03/25 16:42:18 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo p)
{
	if (!p)
		return ;
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
	p->state = 0;
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
	char			*action;

	if (p->state == 0)
		action = "THINKING";
	if (p->state == 1)
		action = "EATING";
	if (p->state == 2)
		action = "SLEEPING";
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	dt = time_diff(tv, p->common->start_time);
	if (p->common->running)
		printf("%ld | Philo %d | Action : %s\n", dt, p->id_philo + 1, action);
	return (0);
}

int	should_run(t_philo p)
{
	if (p->common->max_eat_counter < 0)
		return (p->common->running);
	if	(p->eat_count >= p->common->max_eat_counter)
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
	if(gettimeofday(&(p->last_time_eat), NULL) == -1)
		c->running = 0;
	else
	{
		print_state(p);
		usleep(c->time_to_eat * 1000);
	}
	pthread_mutex_unlock(c->forks + p->id_philo);
	pthread_mutex_unlock(c->forks + ((p->id_philo + 1) % c->nb_philo));
	p->state = 2;
	p->eat_count++;
}

void	*routine_philo(void *arg)
{
	t_philo 		p;

	p = arg;
	if (gettimeofday(&(p->last_time_eat), NULL) == -1)
	{
		p->common->running = 0;
		return (NULL);	
	}
	if (p->id_philo % 2)
		usleep(p->common->time_to_die * 500);
	// printf("should run %d : %d (running %d)\n", p->id_philo, should_run(p), p->common->running);
	while (should_run(p))
	{
		print_state(p);
		if (p->state == 0)
			eat(p, p->common);
		else
		{
			p->state = 0;
			usleep(p->common->time_to_sleep * 1000);
		}
	}
	return (NULL);
}
