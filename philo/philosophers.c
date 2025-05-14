/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:53:07 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/14 13:07:50 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_be_eatin(t_philo *philo)
{
	int	l_fork;
	int	r_fork;
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		l_fork = philo->right_fork;
		r_fork = philo->left_fork;
	}
	else
	{
		l_fork = philo->left_fork;
		r_fork = philo->right_fork;
	}
	pthread_mutex_lock(&data->fork[l_fork]);
	philo_action(philo, "has taken a fork");
	pthread_mutex_lock(&data->fork[r_fork]);
	philo_action(philo, "has taken a fork");
	pthread_mutex_lock(&data->upd_lock);
	philo->time_eaten = get_current_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&data->upd_lock);
	philo_action(philo, "is eating");
	ft_usleep(data->eat_ti, data);
	pthread_mutex_unlock(&data->fork[l_fork]);
	pthread_mutex_unlock(&data->fork[r_fork]);
}

void	*routine(void *args)
{
	t_philo	*philo;
	t_data	*data;
	bool	death;
	
	philo = args;
	data = philo->data;
	if (philo->id % 2 == 1)
		usleep(1000);
	pthread_mutex_lock(&data->time_lock);
	philo->time_eaten = get_current_time();
	pthread_mutex_unlock(&data->time_lock);
	while (1)
	{
		pthread_mutex_lock(&data->death_lock);
		death = data->death;
		pthread_mutex_unlock(&data->death_lock);
		if (death)
			break ;
		philos_eat(philo);
		philo_action(philo, "is sleeping");
		ft_usleep(data->sle_ti, data);
		philo_action(philo, "is thinking");
		ft_usleep(data->sle_ti, data);
	}
	return (NULL);
}

int	philos_eat(t_philo *philo)
{
	t_data *data;
	int	l_fork;

	data = philo->data;
	l_fork = philo->left_fork;
	if (data->death)
		return (-1);
	if (data->philo_no == 1)
	{
		pthread_mutex_lock(&data->fork[l_fork]);
		philo_action(philo, "has taken a fork");
		ft_usleep(data->die_ti, data);
		pthread_mutex_unlock(&data->fork[l_fork]);
		return (0);
	}
	philos_be_eatin(philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 4)
	{
		if (ac < 4)
			printf("girl, you're supposed to give more arguments?\n");
		return (0);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	// argument order: number_of_philosophers | time_to_die | time_to_eat | time_to_sleep
	init_data(data, av);
	create_philos(data);
	clean_up(data);
	return (0);
}
