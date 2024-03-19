/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:12:48 by jules             #+#    #+#             */
/*   Updated: 2024/03/19 11:29:59 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_display(t_common c)
{
	(void) c;
	return ;
}

int	main(int argc, char **argv)
{
	t_common	c;
	t_philo		*ps;

	c = initialize_common(argc, argv);
	ps = create_philo_array(c);
	if (!c || !ps)
		return (EXIT_FAILURE);
	start_display(c);
	run_philo(ps, c);
	free_philo_array(ps, c->nb_philo);
	free_common(c);
	return (EXIT_SUCCESS);
}
