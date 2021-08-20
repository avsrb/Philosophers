/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:37:01 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/18 17:45:53 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <limits.h>

# define DIED	"died"
# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is slepping"
# define THINK	"is thinking"

typedef struct s_ph
{
	pid_t		pid;
	int			ph_id;
	int			ate;
	uint64_t	t_last_meal;
	pthread_t	thread_id;

}			t_ph;

typedef struct s_table
{
	sem_t		*message;
	sem_t		*forks;
	uint64_t	start_time;
	int			nbr_ph;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			must_to_eat;
	int			all_ate;


}			t_table;

typedef struct s_data
{
	t_ph		*ph;
	t_table		*table;
	int			ind_cur;
}			t_data;

// parcing
int			parcing(t_table *table, char **argv);
// init
int			mem_allocation(t_data *data);
int			mem_free(t_data *data);
void		init_philos(t_data *data);
int			init(t_data *data);
int			init_forks(t_table *table);
// printing
int			write_error(char *str);
void		ft_message(t_data *data, int ph_id, char *str);
// time
uint64_t	timestamp(void);
void		ft_sleep(uint64_t time);

#endif