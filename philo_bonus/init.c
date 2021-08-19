/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:45:05 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/18 17:45:10 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	mem_allocation(t_data *d)
{
	d->ph = malloc(sizeof(*d->ph) * d->table->nbr_ph);
	if (d->ph == 0)
		return (-1);
	d->table->forks = malloc(sizeof(*d->table->forks) * d->table->nbr_ph);// надо ли
	if (data->ph == 0)// надо ли
		return (-1);// надо ли
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
	// free(data->table->forks);
	return (0);
}

int	init_forks(t_table *table)
{
	sem_unlink("forks");
	sem_unlink("message");
	table->forks = sem_open("forks", O_CREAT, 0666, table->nbr_ph);
	if (table->forks == 0)
		exit(1);
	table->message = sem_open("message", O_CREAT, 0666, table->nbr_ph);
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
		// d->ph[i].left_fork = &d->table->forks[i];
		// d->ph[i].right_fork = &d->table->forks[(i + 1) % d->table->nbr_ph];
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
	if (init_mutexes(data->table))
		return (write_error("Init mutex"));
	init_philos(data);
	return (0);
}
