/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:12:48 by jules             #+#    #+#             */
/*   Updated: 2024/03/19 05:40:27 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_common	c;
	t_philo		*ps;

	c = initialize_common(argc, argv);
	ps = create_philo_array(c);
	if (!c || !ps)
		return (EXIT_FAILURE);

	free_philo_array(ps, c->nb_philo);
	free_common(c);
	return (EXIT_SUCCESS);
}
