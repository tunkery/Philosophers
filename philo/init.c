/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:51:35 by bolcay            #+#    #+#             */
/*   Updated: 2025/06/04 14:29:21 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t c)
{
	size_t	i;

	i = 0;
	while (i < c && s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < c)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

void	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_no)
	{
		if (pthread_create(&data->philo[i].philos, NULL, &routine, &data->philo[i]) != 0)
			return ;
		i++;
	}
	pthread_create(&data->monitor, NULL, &monitoring, &data->philo[0]);
	i = 0;
	while (i < data->philo_no)
	{
		if (pthread_join(data->philo[i].philos, NULL) == 0)
			return ;
		i++;
	}
	pthread_join(data->monitor, NULL);
}

void	init_data(t_data *data, char **av)
{
	int	i;

	i = 0;
	data->philo_no = ft_atoi(av[1]);
	data->die_ti = ft_atoi(av[2]);
	data->eat_ti = ft_atoi(av[3]);
	data->sle_ti = ft_atoi(av[4]);
	data->eat_no = 0;
	if (av[5])
		data->eat_no = ft_atoi(av[5]);
	data->death = false;
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->msg_lock, NULL);
	pthread_mutex_init(&data->state_mutex, NULL);
	data->start_time = get_current_time();
	data->philo = malloc(sizeof(t_philo) * data->philo_no);
	if (!data->philo)
		return ;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_no);
	if (!data->fork)
		return ;
	while (i < data->philo_no)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		pthread_mutex_init(&data->philo[i].state_mutex, NULL);
		data->philo[i].data = data;
		data->philo[i].meals_eaten = 0;
		data->philo[i].time_eaten = data->start_time;
		data->philo[i].start_time = data->start_time;
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = i + 1;
		if (i == data->philo_no)
			data->philo[i].right_fork = 0;
		else
			data->philo[i].right_fork = i + 2;
		// if (i + 1 < data->philo_no)
		// 	data->philo[i].right_fork = i + 1;
		// else
		// 	data->philo[i].right_fork = 0;
		i++;
	}
}
