/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <mshmelly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:45:05 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/22 20:58:43 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	mem_allocation(t_data *d)
{
	d->ph = malloc(sizeof(*d->ph) * d->table->nbr_ph);
	if (d->ph == 0)
		return (-1);
	return (0);
}

int	mem_free(t_data *data)
{	
	int	i;

	i = 0;
	while (i < data->table->nbr_ph)
	{
		if (pthread_detach(data->ph[i].thread_id))
			return (-1);
		i++;
	}
	free(data->ph);
	return (0);
}

int	init_forks(t_table *table)
{
	sem_unlink("forks");
	sem_unlink("message");
	table->forks = sem_open("forks", O_CREAT, S_IRWXU, table->nbr_ph);
	if (table->forks == 0)
		exit(1);
	table->message = sem_open("message", O_CREAT, S_IRWXU, 1);
	if (table->message == 0)
		exit(1);
	return (0);
}

void	init_philos(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->table->nbr_ph)
	{
		d->ph[i].ph_id = i + 1;
		d->ph[i].ate = 0;
		i++;
	}
	return ;
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	if (mem_allocation(data))
		return (write_error("mem_allocation"));
	if (init_forks(data->table))
		return (write_error("Init sem"));
	init_philos(data);
	return (0);
}
