/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:42:41 by bolcay            #+#    #+#             */
/*   Updated: 2025/06/25 14:04:40 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo, int fork_index)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->fork[fork_index]);
	philo_action(philo, "has taken a fork");
	ft_usleep(data->sle_ti, data);
	pthread_mutex_unlock(&data->fork[fork_index]);
}

int	monitor_helper(t_philo *philo, int i, int *abc)
{
	t_data	*data;
	long	time;

	data = philo->data;
	pthread_mutex_lock(&data->state_mutex);
	time = get_current_time();
	if (time - data->philo[i].time_eaten >= data->die_ti)
	{
		if (data->eat_no > 0 && data->philo[i].m_eaten == data->eat_no
			&& !data->philo[i].full)
			data->philo[i].full = true;
		else if (data->eat_no > 0 && data->philo[i].full)
			(*abc)++;
		else
		{
			print_message(philo, "died", i);
			pthread_mutex_unlock(&data->state_mutex);
			return (-1);
		}
	}
	pthread_mutex_unlock(&data->state_mutex);
	if (data->eat_no > 0 && *abc == data->philo_no)
		return (-1);
	return (0);
}

void	philos_be_thinkin(t_philo *philo, char *message)
{
	t_data	*data;
	long	time;

	data = philo->data;
	pthread_mutex_lock(&data->msg_lock);
	time = get_current_time();
	printf("%ld %d %s\n", time - data->start_time, philo->id, message);
	pthread_mutex_unlock(&data->msg_lock);
	usleep(1000);
}
