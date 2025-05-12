/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhan <batuhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:51:35 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/12 17:12:08 by batuhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_no)
	{
		if (pthread_create(&data->philo[i].philos, NULL, &routine, NULL) != 0)
			return (-1);
		i++;
	}
}

void	init_data(t_data *data, char **av)
{
	int	i;

	i = 0;
	data->philo_no = ft_atoi(av[1]);
	data->die_ti = ft_atoi(av[2]);
	data->eat_ti = ft_atoi(av[3]);
	data->sle_ti = ft_atoi(av[4]);
	if (av[5])
		data->eat_no = ft_atoi(av[5]);
	else
		data->eat_no = 0;
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->time_lock, NULL);
	pthread_mutex_init(&data->action_lock, NULL);
	get_time(data);
	data->philo = malloc(sizeof(t_philo) * data->philo_no);
	if (!data->philo)
		return (0);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_no);
	if (!data->fork)
		return (0);
	while (i < data->philo_no)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		data->philo[i].meals_eaten = 0;
		data->philo[i].time_eaten = 0;
		data->philo[i].id = i + 1;
		data->philo[i].death = false;
		data->philo[i].left_fork = i + 1;
		if (i + 1 < data->philo_no)
			data->philo[i].right_fork = i + 2;
		else
			data->philo[i].right_fork = 1;
		i++;
	}
}
