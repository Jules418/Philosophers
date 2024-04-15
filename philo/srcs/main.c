/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:12:48 by jules             #+#    #+#             */
/*   Updated: 2024/04/15 10:48:17 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_philo(t_philo *ps, t_common c)
{
	int			i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * (c->nb_philo + 1));
	if (!threads)
		return (1);
	i = -1;
	pthread_mutex_lock(&(c->starting_mutex));
	while (++i < c->nb_philo)
	{
		if (pthread_create(threads + i, NULL, routine_philo, ps[i]))
		{
			set_running(c, 0);
			break ;
		}
	}
	if (pthread_create(threads + i, NULL, dead_checker, ps))
		set_running(c, 0);
	pthread_mutex_unlock(&(c->starting_mutex));
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	set_running(c, 0);
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
	if (gettimeofday(&(c->start_time), NULL) == 0)
		if (run_philo(ps, c))
			exit_state = EXIT_FAILURE;
	free_philo_array(ps, c->nb_philo);
	free_common(c);
	return (exit_state);
}

//valgrind --tool=helgrind --tool=drd ./philo 4 800 200 200 