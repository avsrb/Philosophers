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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		t_last_meal;

}			t_ph;

typedef struct s_table
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		message;

	int		nbr_ph;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		must_to_eat;

	int			dieded;
	int			all_ate;
	long long		start_time;

}			t_table;


typedef struct s_data
{
	t_ph		*ph;
	t_table		*table;
	int			ind_cur;
}			t_data;


/*
*	parcing
*/
int	parcing(t_table *table, char **argv);


int	write_error(char *str);



#endif