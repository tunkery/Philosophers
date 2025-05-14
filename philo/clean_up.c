/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:35:26 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/14 21:05:16 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death_lock);
	// pthread_mutex_destroy(&data->time_lock);
	// pthread_mutex_destroy(&data->action_lock);
	// pthread_mutex_destroy(&data->upd_lock);
	pthread_mutex_destroy(&data->msg_lock);
	pthread_mutex_destroy(&data->state_mutex);
	// pthread_mutex_destroy(&data->sleep_lock);
	// pthread_mutex_destroy(&data->think_lock);
	while (i < data->philo_no)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].state_mutex);
		i++;
	}
	free(data->philo);
	free(data->fork);
}
