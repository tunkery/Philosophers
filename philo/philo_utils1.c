/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:11:15 by bolcay            #+#    #+#             */
/*   Updated: 2025/06/20 13:29:04 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_for_eat(t_philo *philo, char *message, long time)
{
	t_data	*data;
	bool	check;

	data = philo->data;
	pthread_mutex_lock(&data->msg_lock);
	pthread_mutex_lock(&data->death_lock);
	check = data->death;
	pthread_mutex_unlock(&data->death_lock);
	if (check)
	{
		pthread_mutex_unlock(&data->msg_lock);
		return (-1);
	}
	printf("%ld %d %s\n", time - data->start_time, philo->id, message);
	pthread_mutex_unlock(&data->msg_lock);
	return (0);
}

bool	death_check(t_philo *philo)
{
	t_data	*data;
	bool	check;

	data = philo->data;
	pthread_mutex_lock(&data->death_lock);
	check = data->death;
	pthread_mutex_unlock(&data->death_lock);
	return (check);
}

int	thinking(t_philo *philo, char *message)
{
	t_data	*data;
	bool	check;
	long	time;

	data = philo->data;
	pthread_mutex_lock(&data->state_mutex);
	time = get_current_time();
	if (time - philo->time_eaten >= data->die_ti)
	{
		pthread_mutex_unlock(&data->state_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&data->state_mutex);
	pthread_mutex_lock(&data->msg_lock);
	pthread_mutex_lock(&data->death_lock);
	check = data->death;
	pthread_mutex_unlock(&data->death_lock);
	if (check)
	{
		pthread_mutex_unlock(&data->msg_lock);
		return (-1);
	}
	printf("%ld %d %s\n", time - data->start_time, philo->id, message);
	pthread_mutex_unlock(&data->msg_lock);
	ft_usleep(data->die_ti - (data->eat_ti + data->sle_ti) * 1000, data);
	// usleep(data->die_ti - (data->eat_ti + data->sle_ti) * 1000);
	return (0);
}

int	ft_usleep(long ms, t_data *data)
{
	long	c_time;

	c_time = get_current_time();
	while ((get_current_time() - c_time) < ms)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->death)
		{
			pthread_mutex_unlock(&data->death_lock);
			return (-1);
		}
		pthread_mutex_unlock(&data->death_lock);
		usleep(100);
	}
	return (0);
}

int	eat(t_philo *philo, char *message)
{
	t_data	*data;
	// bool	check;
	long	time;

	data = philo->data;
	pthread_mutex_lock(&data->state_mutex);
	time = get_current_time();
	if (time - philo->time_eaten >= data->die_ti)
	{
		pthread_mutex_unlock(&data->state_mutex);
		return (-1);
	}
	philo->meals_eaten++;
	philo->time_eaten = time;
	pthread_mutex_unlock(&data->state_mutex);
	if (print_for_eat(philo, message, time) == -1)
		return (-1);
	if (ft_usleep(data->eat_ti, data) == -1)
		return (-1);
	return (0);
}
