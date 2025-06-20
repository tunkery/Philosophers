/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:08:11 by bolcay            #+#    #+#             */
/*   Updated: 2025/06/20 11:01:56 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_be_eatin(t_philo *philo)
{
	t_data	*data;
	int		left;
	int		right;

	data = philo->data;
	// if (philo->id == data->philo_no)
	// {
	// 	left = philo->left_fork;
	// 	right = philo->right_fork;
	// }
	if (philo->id % 2)
	{
		left = philo->right_fork;
		right = philo->left_fork;
	}
	else
	{
		right = philo->right_fork;
		left = philo->left_fork;
	}
	pthread_mutex_lock(&data->fork[left]);
	philo_action(philo, "has taken a fork");
	pthread_mutex_lock(&data->fork[right]);
	philo_action(philo, "has taken a fork");
	eat(philo, "is eating");
	// if (philo_action(philo, "has taken a fork") == -1)
	// {
	// 	pthread_mutex_unlock(&data->fork[left]);
	// 	return (-1);
	// }
	// pthread_mutex_lock(&data->fork[right]);
	// if (philo_action(philo, "has taken a fork") == -1)
	// {
	// 	pthread_mutex_unlock(&data->fork[left]);
	// 	pthread_mutex_unlock(&data->fork[right]);
	// 	return (-1);
	// }
	// if (eat(philo, "is eating") == -1)
	// {
	// 	pthread_mutex_unlock(&data->fork[left]);
	// 	pthread_mutex_unlock(&data->fork[right]);
	// 	return (-1);
	// }
	pthread_mutex_unlock(&data->fork[left]);
	pthread_mutex_unlock(&data->fork[right]);
	return (0);
}

int	beginning_of_eat(t_philo *philo)
{
	t_data	*data;
	// int		id;
	int		fork_index;

	data = philo->data;
	// id = philo->id;
	fork_index = philo->left_fork;
	if (data->philo_no == 1)
	{
		pthread_mutex_lock(&data->fork[fork_index]);
		philo_action(philo, "has taken a fork");
		ft_usleep(data->sle_ti, data);
		pthread_mutex_unlock(&data->fork[fork_index]);
		return (-1);
	}
	if (philos_be_eatin(philo) == -1)
		return (-1);
	return (0);
}

int	philo_action(t_philo *philo, char *message)
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
	// pthread_mutex_lock(&data->death_lock);
	// check = data->death;
	// pthread_mutex_unlock(&data->death_lock);
	// if (check)
	// 	return (-1);
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

int	sleepin(t_philo *philo, char *message)
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
	// pthread_mutex_lock(&data->death_lock);
	// check = data->death;
	// pthread_mutex_unlock(&data->death_lock);
	// if (check)
	// 	return (-1);
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
	if (ft_usleep(data->sle_ti, data) == -1)
		return (-1);
	return (0);
}
