/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:35:09 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/09 13:35:12 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(struct timeval time1)
{
	struct timeval	time2;
	struct timeval	difference;

	gettimeofday(&time2, NULL);
	difference.tv_sec = time2.tv_sec - time1.tv_sec;
	difference.tv_usec = time2.tv_usec - time1.tv_usec;
	if (difference.tv_usec < 0)
	{
		--difference.tv_sec;
		difference.tv_usec += 1000000;
	}
	return (difference.tv_sec * 1000 + difference.tv_usec / 1000);
}

void	my_usleep(long time, struct timeval now)
{
	long long	cur_time;

	cur_time = time_now(now);
	while (1)
	{
		usleep(100);
		if (time_now(now) == cur_time + time)
			break ;
	}
}




int	write_error(char *str)
{
	int	len;
	
	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 8);
	write(2, str, len);
	write(2, "\n", 1);
	return(1);
}

void	ft_message(t_data *data, int ph_id, char *str)
{
	pthread_mutex_lock(&data->message);
	if(!(data->dieded))
	{	
		printf("%lld ", timestamp() - data->start_time);
		printf("%d %s\n", ph_id, str);
	}
	pthread_mutex_unlock(&data->message);
}

int	death_checker(t_data *data, t_ph *ph)
{
	int	i;

	while(!(data->all_ate))
	{	
		i = 0;
		while (data->nbr_ph > i && !(data->dieded))
		{
			if (data->time_die < timestamp() - ph[i].t_last_meal)
			{
				ft_message(data, i, "died");
				data->dieded = 1;
				return (1);
			}
			i = 0;
			while (data->nbr_times_ph_must_eat != -1 && data->nbr_ph > i && data->time_die)
				i++;
			if (i == data->nbr_ph)
				data->all_ate = 1;
			usleep(50);
			i++;
		}
	}
	return (0);
}

void	ph_eat(t_ph *ph)
{
	t_data	*data = ph->data;

	pthread_mutex_lock(&data->forks[ph->left_fork]);
	ft_message(data, ph->ph_id, "has taken a left fork");
	pthread_mutex_lock(&data->forks[ph->right_fork]);
	ft_message(data, ph->ph_id, "has taken a right fork");
	ph->t_last_meal = timestamp();
	ph->ate++;
	ft_message(data, ph->ph_id, "is eating");
	ft_sleep(data->time_eat, data);
	pthread_mutex_unlock(&data->forks[ph->left_fork]);
	pthread_mutex_unlock(&data->forks[ph->right_fork]);
}

void	*ft_thread(void *void_philo)
{
	t_ph	*ph =(void *)void_philo;
	t_data	*data = ph->data;

	if (ph->ph_id % 2) // убрать если переделаю запуск потоков
		usleep(100);
	while(!(data->dieded))
	{
		ph_eat(ph);
		if (data->all_ate)
			break ;
		ft_message(data, ph->ph_id, "is slepping");
		ft_sleep(data->time_sleep, data);
		ft_message(data, ph->ph_id, "is thinking");
	}
	return (NULL);
}

int	create_mutex(t_data *data)
{
	int	i;
	
	i = 0;
	while (data->nbr_ph > i++)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (write_error("mutex_forks"));//
	}
	if (pthread_mutex_init(&data->message, NULL))
		return(write_error("mutex_message"));//
	return (0);
}

int	create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = timestamp();
	while (data->nbr_ph > i++)
	{
		data->ph[i].ph_id = i;
		data->ph[i].left_fork = i;
		data->ph[i].right_fork = (i + 1) % data->nbr_ph; // del % 
		data->ph[i].ate = 0;
		data->ph[i].t_last_meal = 0;
		data->ph[i].data = data;

	}
	i = 0;
	while (data->nbr_ph > i++)
	{
		data->ph[i].t_last_meal = timestamp();
		if (pthread_create(&data->ph[i].thread_id, NULL, ft_thread, &(data->ph[i])) != 0)
			return (-1);
		usleep(100);
	}
	death_checker(data, data->ph);
	i = 0;
	while (data->nbr_ph > i++)
	{
		if (pthread_join((data->ph[i].thread_id), NULL) != 0)
			return (-1);
	}
	i = 0;
	while (data->nbr_ph > i++)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->message);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return(write_error("Not enough arguments"));
	if (parcing(&data, argv))
		return(write_error("Incorrect_arguments"));
	data.ph = malloc(sizeof(*data.ph) * data.nbr_ph);
	data.forks = malloc(sizeof(*data.ph) * data.nbr_ph);
	if (create_mutex(&data))
		return(write_error("create forks"));
	if (create_philo(&data))
		return(write_error("create philo"));

	
	return (0);
}

/*	- Каждый философ - отдельный поток
*	- операции "захват/освобождения" вилки реализуются через мьютексы
*	- захват вилок происходит иерархически
*	
*/	

