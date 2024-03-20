/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 04:56:49 by jules             #+#    #+#             */
/*   Updated: 2024/03/20 17:01:25 by jbanacze         ###   ########.fr       */
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
	p->last_time_eat = 0;
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

void	*routine_philo(void *arg)
{
	t_philo 		p;
	struct timeval	tv;

	p = arg;
	gettimeofday(&tv, NULL);
	p->last_time_eat = tv.tv_sec;
	printf("time : %d\n", p->last_time_eat);
	return (NULL);
}
