/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhan <batuhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:53:07 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/12 16:49:02 by batuhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args, t_data *data)
{
	bool	death;
	
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
