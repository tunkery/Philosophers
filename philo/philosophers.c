/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhan <batuhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:53:07 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/13 15:26:50 by batuhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_be_eatin(t_data *data)
{
	int	l_fork;
	int	r_fork;

	l_fork = data->philo->left_fork;
	r_fork = data->philo->right_fork;
	pthread_mutex_lock(&data->fork[l_fork]);
	philo_action(data, "has taken a fork");
	pthread_mutex_lock(&data->fork[r_fork]);
	philo_action(data, "has taken a fork");
	philo_action(data, "is eating");
	pthread_mutex_lock(&data->upd_lock);
	data->philo->meals_eaten += 1;
	data->philo->time_eaten = get_current_time;
	pthread_mutex_unlock(&data->upd_lock);
	ft_usleep(data->eat_ti, data);
	pthread_mutex_unlock(&data->fork[l_fork]);
	pthread_mutex_unlock(&data->fork[r_fork]);
}

void	*routine(void *args, t_data *data)
{
	bool	death;
	
	if (data->philo->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&data->time_lock);
	data->philo->time_eaten = get_current_time();
	pthread_mutex_unlock(&data->time_lock);
	while (1)
	{
		pthread_mutex_lock(&data->death_lock);
		death = data->philo->death;
		pthread_mutex_unlock(&data->death_lock);
		if (death)
			break ;
		// here i will add the action function for thinking and sleeping
	}
}

int	before_routine(t_data *data)
{
	
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 4 || check_args(av) == -1)
	{
		if (ac < 4)
			printf("girl, you're supposed to give more arguments??!?!?\n");
		else
			printf("Invalid argument\n");
		return (0);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	// argument order: number_of_philosophers | time_to_die | time_to_eat | time_to_sleep
	init_data(data, av);
	return (0);
}
