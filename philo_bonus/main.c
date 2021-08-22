/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <mshmelly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:35:09 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/22 20:51:40 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_data *data, t_ph *ph)
{
	sem_wait(data->table->forks);
	ft_message(data, ph->ph_id, LFORK);
	sem_wait(data->table->forks);
	ft_message(data, ph->ph_id, RFORK);
	if (timestamp() - ph->t_last_meal > data->table->t_die)
	{
		sem_wait(data->table->forks);
	}
	ph->t_last_meal = timestamp();
	ft_message(data, ph->ph_id, EAT);
	ft_sleep(data->table->t_eat);
	sem_post(data->table->forks);
	sem_post(data->table->forks);
	ph->ate++;
	ft_message(data, ph->ph_id, SLEEP);
	ft_sleep(data->table->t_sleep);
	ft_message(data, ph->ph_id, THINK);
}

void	*ph_life(void *v_data)
{
	t_data	*d;

	d = v_data;
	d->ph->t_last_meal = timestamp();
	d->ph->ph_id = d->ind_cur;
	while (1)
	{
		eating(d, d->ph);
	}
}

void	child_life(t_data *d)
{
	if (pthread_create(&d->ph->thread_id, NULL, ph_life, d))
		exit(1);
	while (1)
	{
		usleep(500);
		if (timestamp() - d->ph->t_last_meal > d->table->t_die)
		{
			ft_message(d, d->ph->ph_id, DIED);
			exit (1);
		}
		if (d->ph->ate > d->table->must_to_eat \
			&& d->table->must_to_eat != INT_MAX)
		{
			exit (1);
		}
	}
}

int	creating_philos(t_data *data)
{
	int	i;

	i = 0;
	data->table->start_time = timestamp();
	while (i < data->table->nbr_ph)
	{	
		data->ind_cur = i;
		data->ph[i].pid = fork();
		usleep(50);
		if (data->ph[i].pid == 0)
		{
			child_life(data);
			exit(1);
		}
		else
			i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_data	data;
	int		i;
	int		status;

	data.table = &table;
	i = 0;
	if (argc < 5 || argc > 6)
		return (write_error("Not enough arguments"));
	if (parcing(&table, argv))
		return (write_error("Incorrect_arguments"));
	if (init(&data))
		return (write_error("Init"));
	if (creating_philos(&data))
		return (write_error("Create pthreads"));
	mem_free(&data);
	waitpid(-1, &status, 0);
	while (i < data.table->nbr_ph)
	{
		kill(data.ph[i].pid, SIGKILL);
		i++;
	}
	return (0);
}
