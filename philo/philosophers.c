/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:53:07 by bolcay            #+#    #+#             */
/*   Updated: 2025/06/06 17:01:05 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message, int i)
{
	t_data	*data;
	long	time;

	data = philo->data;
	pthread_mutex_lock(&data->death_lock);
	data->death = true;
	pthread_mutex_unlock(&data->death_lock);
	time = get_current_time();
	pthread_mutex_lock(&data->msg_lock);
	printf("%ld %d %s\n", time - data->start_time, i + 1, message);
	pthread_mutex_unlock(&data->msg_lock);
}

void	*monitoring(void *args)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = args;
	data = philo->data;
	i = 0;
	while (1)
	{
		while (i < data->philo_no)
		{
			pthread_mutex_lock(&data->state_mutex);
			if (get_current_time() - data->philo[i].time_eaten >= data->die_ti)
			{
				print_message(philo, "died", i);
				pthread_mutex_unlock(&data->state_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->state_mutex);
			i++;
		}
		i = 0;
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;
	t_data	*data;

	philo = args;
	data = philo->data;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (data->eat_no > 0)
		{
			pthread_mutex_lock(&data->state_mutex);
			if (philo->meals_eaten == data->eat_no)
			{
				pthread_mutex_unlock(&data->state_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->state_mutex);
		}
		if (beginning_of_eat(philo) == -1)
			break ;
		if (sleepin(philo, "is sleeping") == -1)
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		check;

	if (ac < 5)
	{
		printf("girl, you're supposed to give more arguments?\n");
		return (0);
	}
	check = check_args(av);
	if (check == -2)
	{
		printf("Argument values must be more than 0\n");
		return (0);
	}
	if (check == -1)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (init_arguments(data, av) == -1)
		return (0);
	create_philos(data);
	clean_up(data);
	return (0);
}
