/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:12:48 by jules             #+#    #+#             */
/*   Updated: 2024/03/26 08:09:54 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_display(t_common c)
{
	(void) c;
	return ;
}

int	run_philo(t_philo *ps, t_common c)
{
	int			i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * (c->nb_philo + 1));
	if (!threads)
		return (1);
	i = -1;
	while (++i < c->nb_philo)
	{
		if (pthread_create(threads + i, NULL, routine_philo, ps[i]))
		{
			c->running = 0;
			break ;
		}
	}
	if (pthread_create(threads + i, NULL, dead_checker, ps))
		c->running = 0;
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	c->running = 0;
	pthread_join(threads[c->nb_philo], NULL);
	free(threads);
	return (0);
}

int	main(int argc, char **argv)
{
	t_common	c;
	t_philo		*ps;
	int			exit_state;

	exit_state = EXIT_SUCCESS;
	c = initialize_common(argc, argv);
	ps = create_philo_array(c);
	if (!c || !ps)
		return (EXIT_FAILURE);
	start_display(c);
	if (gettimeofday(&(c->start_time), NULL) == 0)
		if (run_philo(ps, c))
			exit_state = EXIT_FAILURE;
	free_philo_array(ps, c->nb_philo);
	free_common(c);
	return (exit_state);
}
