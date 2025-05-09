/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:51:35 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/09 17:30:33 by bolcay           ###   ########.fr       */
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
	data->time = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_no);
	if (!data->philo)
		return (0);
	while (i < data->philo_no)
	{
		data->philo[i].meals_eaten = 0;
		data->philo[i].id = i + 1;
	}
}
