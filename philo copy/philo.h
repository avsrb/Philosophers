/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:37:01 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/09 13:37:03 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>


typedef struct s_ph
{
	pthread_t		thread_id;
	int				ph_id;
	int				ate;
	int				left_fork;
	int				right_fork;
	long long		t_last_meal;
	struct s_data	*data;

}			t_ph;

typedef struct s_data
{
	t_ph	*ph;
	pthread_mutex_t		*forks;
	pthread_mutex_t		message;

	int		nbr_ph;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nbr_times_ph_must_eat;

	int		dieded;
	int		all_ate;
	long long		start_time;


}			t_data;


/*
*	parcing
*/
int	parcing(t_data *data, char **argv);


int	write_error(char *str);



#endif
