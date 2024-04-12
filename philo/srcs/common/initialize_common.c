/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_common.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:51:19 by jules             #+#    #+#             */
/*   Updated: 2024/04/12 21:18:55 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_fork *forks, int size)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&(forks[i].mutex));
		i++;
	}
	free(forks);
}

void	free_common(t_common c)
{
	if (!c)
		return ;
	free_forks(c->forks, c->nb_philo);
	pthread_mutex_destroy(&(c->running_mutex));
	free(c);
}

t_fork	*initialize_forks(int nb_philo)
{
	t_fork	*forks;
	int				i;

	if (nb_philo < 1)
		return (NULL);
	forks = malloc(sizeof(t_fork) * nb_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb_philo)
	{
		forks[i].taken = 0;
		forks[i].id_philo = -1;
		forks[i].mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		i++;
	}
	return (forks);
}

int	errors_in_common(t_common c)
{
	if (c->nb_philo < 0)
		return (1);
	if (c->time_to_die < 0)
		return (1);
	if (c->time_to_eat < 0)
		return (1);
	if (c->time_to_sleep < 0)
		return (1);
	if (!(c->forks))
		return (1);
	return (0);
}

t_common	initialize_common(int argc, char **argv)
{
	t_common	c;
	int			err;

	if ((argc != 5) && (argc != 6))
		return (NULL);
	c = malloc(sizeof(struct s_common));
	if (!c)
		return (NULL);
	err = 0;
	c->nb_philo = ft_atoi(argv[1], &err);
	c->time_to_die = ft_atoi(argv[2], &err);
	c->time_to_eat = ft_atoi(argv[3], &err);
	c->time_to_sleep = ft_atoi(argv[4], &err);
	if (argc == 6)
		c->max_eat_counter = ft_atoi(argv[5], &err);
	else
		c->max_eat_counter = -1;
	c->running = 1;
	c->running_mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	c->forks = initialize_forks(c->nb_philo);
	if (err || errors_in_common(c))
		return (free_common(c), NULL);
	return (c);
}
