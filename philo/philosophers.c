/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:53:07 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/14 21:12:28 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message1(t_philo *philo, char *message)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->msg_lock);
	if (!data->death || ft_strncmp(message, "died", 4) == 0)
		printf("%ld %d %s\n", get_current_time() - data->start_time, data->philo->id, message);
	pthread_mutex_unlock(&data->msg_lock);
}

int	philos_be_eatin(t_philo *philo)
{
	int	l_fork;
	int	r_fork;
	t_data	*data;

	data = philo->data;
	// if (philo->right_fork == 0)
	// {
	// 	l_fork = philo->right_fork;
	// 	r_fork = philo->left_fork;
	// }
	if (philo->id % 2 == 0)
	{
		l_fork = philo->right_fork;
		r_fork = philo->left_fork;
	}
	else
	{
		// usleep(500);
		l_fork = philo->left_fork;
		r_fork = philo->right_fork;
	}
	pthread_mutex_lock(&data->fork[l_fork]);
	if (philo_action(philo, "has taken a fork") == -1)
	{
		pthread_mutex_unlock(&data->fork[l_fork]);
		return (-1);
	}
	pthread_mutex_lock(&data->fork[r_fork]);
	if (philo_action(philo, "has taken a fork") == -1)
	{
		pthread_mutex_unlock(&data->fork[l_fork]);
		pthread_mutex_unlock(&data->fork[r_fork]);
		return (-1);
	}
	pthread_mutex_lock(&data->state_mutex);
	philo->time_eaten = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->state_mutex);
	if (philo_action(philo, "is eating") == -1)
	{
		pthread_mutex_unlock(&data->fork[l_fork]);
		pthread_mutex_unlock(&data->fork[r_fork]);
		return (-1);
	}
	if (ft_usleep(data->eat_ti, data) == -1)
	{
		pthread_mutex_unlock(&data->fork[l_fork]);
		pthread_mutex_unlock(&data->fork[r_fork]);
		return (-1);
	}
	pthread_mutex_unlock(&data->fork[l_fork]);
	pthread_mutex_unlock(&data->fork[r_fork]);
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;
	t_data	*data;
	bool	death;
	
	philo = args;
	death = false;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_usleep(15, data);
	// else
	// 	usleep(200);
	pthread_mutex_lock(&data->state_mutex);
	philo->time_eaten = get_current_time();
	pthread_mutex_unlock(&data->state_mutex);
	while (1)
	{
		if (death)
			break ;
		pthread_mutex_lock(&data->death_lock);
		death = data->death;
		pthread_mutex_unlock(&data->death_lock);
		if (death)
			break ;
		if (philos_eat(philo) == -1)
			break ;
		if (philo_action(philo, "is sleeping") == -1)
			break ;
		if (ft_usleep(data->sle_ti, data) == -1)
			break ;
		// usleep(50);
		if (philo_action(philo, "is thinking") == -1)
			break ;
		pthread_mutex_lock(&data->state_mutex);
		if ((get_current_time() - philo->time_eaten) > data->die_ti)
		{
			pthread_mutex_lock(&data->death_lock);
			data->death = true;
			print_message1(philo, "died");
			pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_unlock(&data->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->state_mutex);
		if (data->philo_no % 2 == 1 && data->sle_ti <= data->eat_ti)
		{
			usleep((data->eat_ti - data->sle_ti) * 1000);
			usleep(1000);
		}
		// usleep(1000);
		// ft_usleep(data->sle_ti, data);
	}
	return (NULL);
}

int	philos_eat(t_philo *philo)
{
	t_data *data;
	int	l_fork;

	data = philo->data;
	pthread_mutex_lock(&data->death_lock);
	if (data->death)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (-1);
	}
	pthread_mutex_unlock(&data->death_lock);
	l_fork = philo->left_fork;
	// usleep(50);
	pthread_mutex_lock(&data->state_mutex);
	if (philo->meals_eaten == data->eat_no && data->eat_no != 0)
	{
		pthread_mutex_unlock(&data->state_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->state_mutex);
	if (data->philo_no == 1)
	{
		pthread_mutex_lock(&data->fork[l_fork]);
		philo_action(philo, "has taken a fork");
		ft_usleep(data->die_ti, data);
		pthread_mutex_unlock(&data->fork[l_fork]);
		return (0);
	}
	if (philos_be_eatin(philo) == -1)
		return (-1);
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
