/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhan <batuhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:51:35 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/11 21:34:50 by batuhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_data *data)
{
}

void	init_data(t_data *data, t_philo *philo, char **av)
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
	get_time(data);
	data->philo = malloc(sizeof(t_philo) * data->philo_no);
	if (!data->philo)
		return (0);
	while (i < data->philo_no)
	{
		pthread_mutex_init(&data->philo[i].lock, NULL);
		data->philo[i].meals_eaten = 0;
		data->philo[i].id = i + 1;
		data->philo[i].death = false;
	}
}
