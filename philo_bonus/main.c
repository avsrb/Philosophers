/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:35:09 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/18 17:45:23 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	monitoring(t_data *data, int i)
{
	while (1)
	{
		i = 0;
		while (i++ < data->table->nbr_ph)
		{
			if (timestamp() - data->ph[i].t_last_meal > data->table->t_die)
			{
				ft_message(data, data->ph->ph_id, DIED);
				return (1);
			}
			i = 0;
			while (i < data->table->nbr_ph && data->ph[i].ate \
				< data->table->must_to_eat)
				i++;
			if (i < data->table->nbr_ph)
			{
				// pthread_mutex_lock(&data->table->message);
				write (1, "THE END\n", 8);
				return (1);
			}
			usleep (500);
		}
	}
	return (0);
}

void	eating(t_data *data, t_ph *ph)
{
	// sem_wait(data->table->forks);
	ft_message(data, ph->ph_id, FORK);
	// sem_wait(data->table->forks);
	ft_message(data, ph->ph_id, FORK);
	if (data->table->must_to_eat == ph->ate)
		data->table->all_ate++;
	if (timestamp() - ph->t_last_meal > data->table->t_die)
		// sem_wait(data->table->forks);
	ph->t_last_meal = timestamp();
	ft_message(data, ph->ph_id, EAT);
	ft_sleep(data->table->t_eat);
	ph->ate++;
	write(1, "tuta\n", 5);
	// sem_post(data->table->forks);
	// sem_post(data->table->forks);
}

void	*life(void *v_data)
{

	t_data	*data;
	t_ph	*ph;

	data = v_data;
	// ph = data->ph + data->ind_cur;
	// ph->t_last_meal = timestamp();
	while (1)
	{
		eating(data, ph);
		ft_message(data, ph->ph_id, SLEEP);
		ft_sleep(data->table->t_sleep);
		ft_message(data, ph->ph_id, THINK);
	}
}

void	child_life(t_data *d)
{
	if (pthread_create(&d->ph->thread_id, NULL, life, d))
		exit(1);
	usleep(100);
	while (1)
	{
		if (timestamp() - d->ph->t_last_meal > d->table->t_die)
		{
			ft_message(d, d->ph->ph_id, DIED);
			exit (1);
		}
		if (d->ph->ate < d->table->must_to_eat) // && d->table->must_to_eat != INT_MAX)
		{
			// pthread_mutex_lock(&data->table->message);
			// sem_wait(d->table->message);
			write (1, "THE END\n", 8);
			exit (1);
		}
		usleep (500);
	}
}


int	creating_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nbr_ph)
	{
		data->table->start_time = timestamp();
		// data->ind_cur = i;
		data->ph[i - 1].pid = fork();
		if (data->ph[i - 1].pid)
			i++;
		else
		{
			child_life(data);
			exit(1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_data	data;

	data.table = &table;
	if (argc < 5 || argc > 6)
		return (write_error("Not enough arguments"));
	if (parcing(&table, argv))
		return (write_error("Incorrect_arguments"));
	if (init(&data))
		return (write_error("Init"));
	if (creating_philos(&data))
		return (write_error("Create pthreads"));
	// monitoring(&data, 0);
	mem_free(&data);
	return (0);
}
