/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:35:26 by bolcay            #+#    #+#             */
/*   Updated: 2025/06/06 14:48:13 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->msg_lock);
	pthread_mutex_destroy(&data->state_mutex);
	while (i < data->philo_no)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->philo);
	free(data->fork);
	free(data);
}
