/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:53:38 by jules             #+#    #+#             */
/*   Updated: 2024/03/18 11:56:59 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s, int *err_code)
{
	size_t			i;
	int				sign;
	unsigned int	n;

	n = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	if ((s[i] < '0') || ('9' < s[i]))
		*err_code = 1;
	while (s[i] && (('0' <= s[i]) && (s[i] <= '9')))
	{
		n = n * 10 + (s[i] - '0');
		if (n > ((unsigned int) INT_MAX + 1 * (sign == -1)))
			break ;
		i++;
	}
	if (s[i])
		*err_code = 1;
	return (n * sign);
}
