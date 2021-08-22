/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <mshmelly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:46:09 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/22 20:53:27 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

uint64_t	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}


void	ft_sleep(uint64_t time)
{
	uint64_t	start;
	uint64_t	current;

	start = timestamp();
	current = start;
	while (time > timestamp() - start)
	{
		current = timestamp();
		usleep(300);
	}
	return ;
}
