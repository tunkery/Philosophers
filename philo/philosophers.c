/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:53:07 by bolcay            #+#    #+#             */
/*   Updated: 2025/06/06 14:01:04 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message, int i)
{
	t_data	*data;
	long	time;

	data = philo->data;
	time = get_current_time();
	pthread_mutex_lock(&data->msg_lock);
	printf("%ld %d %s\n", time - data->start_time, i + 1, message);
	pthread_mutex_unlock(&data->msg_lock);
}

void	*monitoring(void *args)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = args;
	data = philo->data;
	i = 0;
	while (1)
	{
		while (i < data->philo_no)
		{
			pthread_mutex_lock(&data->state_mutex);
			if (get_current_time() - data->philo[i].time_eaten > data->die_ti)
			{
				pthread_mutex_lock(&data->death_lock);
				data->death = true;
				pthread_mutex_unlock(&data->death_lock);
				print_message(philo, "died", i);
				pthread_mutex_unlock(&data->state_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->state_mutex);
			i++;
		}
		// if (check)
		// {
		// 	print_message(philo, "died", i);
		// 	return (NULL);
		// }
		i = 0;
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;
	t_data	*data;

	philo = args;
	data = philo->data;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (data->eat_no > 0)
		{
			pthread_mutex_lock(&data->state_mutex);
			if (philo->meals_eaten == data->eat_no)
			{
				pthread_mutex_unlock(&data->state_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->state_mutex);
		}
		if (beginning_of_eat(philo) == -1)
			break ;
		// forklari aldi, yemeye basladi
		if (sleepin(philo, "is sleeping") == -1)
			break ;
		// if (thinking(philo, "is thinking") == -1)
		// 	break ;
	}
	return (NULL);
}

int	philos_be_eatin(t_philo *philo)
{
	t_data	*data;
	int		left;
	int		right;

	data = philo->data;
	// if (philo->right_fork == 0)
	// {
	// 	left = philo->right_fork;
	// 	right = philo->left_fork;
	// }
	if (philo->id % 2)
	{
		left = philo->right_fork;
		right = philo->left_fork;
	}
	else
	{
		// usleep(500);
		right = philo->right_fork;
		left = philo->left_fork;
	}
	pthread_mutex_lock(&data->fork[left]);
	philo_action(philo, "has taken a fork");
	pthread_mutex_lock(&data->fork[right]);
	philo_action(philo, "has taken a fork");
	eat(philo, "is eating");
	pthread_mutex_unlock(&data->fork[left]);
	pthread_mutex_unlock(&data->fork[right]);
	return (0);
}

int	beginning_of_eat(t_philo *philo)
{
	t_data	*data;
	int		id;

	data = philo->data;
	id = philo->id;
	if (data->philo_no == 1)
	{
		pthread_mutex_lock(&data->fork[id]);
		philo_action(philo, "has taken a fork");
		ft_usleep(data->sle_ti, data);
		pthread_mutex_unlock(&data->fork[id]);
		return (-1);
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
	if (init_data(data, av) == -1)
		return (0);
	create_philos(data);
	clean_up(data);
	return (0);
}
