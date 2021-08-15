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

#include "philo_one.h"

pthread_t t1, t2; //индефикатор потока

void	*print1(void *buf)
{
	//pthread_detach(t1); // эта функция позволяет работать
						//потоку самостоятельно или все же можно применить pthread_join в вызывающей функции
	for (int i = 0; i < 10; i++)
	{
		write (1, (char *)buf, strlen(buf));
		usleep(10000);
	}
	return (NULL);
}

void	*print2(void *buf)
{
	//pthread_detach(t2);
	for (int i = 0; i < 10; i++)
	{
		write (1, (char *)buf, strlen(buf));
		usleep(10000);
	}
	return (NULL);
}

void	threads(void)
{
	char *str1 = "1_1_1_1_1_1_1_1_1_1_1\n";
	char *str2 = "_2_2_2_2_2_2_2_2_2_2_2\n";


	pthread_create(&t1, NULL, print1, (void *)str1); //(принимает: t1 - индефикатор потока, 2 - атрибуты, 3 - указатель на фукцию, 4 - аргументы которая принимается функция)
	pthread_create(&t2, NULL, print2, (void *)str2); //в этих функциях выделяется память

	pthread_join(t1, NULL); // поток завершается либо ретерн либо питред exit
	pthread_join(t2, NULL);
	
	write(1, "Exit\n", 5);
}

int	main(void)
{
	threads();
	return (0);
}
