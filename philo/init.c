/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhan <batuhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:51:35 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/13 17:06:36 by batuhan          ###   ########.fr       */
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

void	print_message(t_data *data, char *message, int i)
{
	pthread_mutex_lock(&data->msg_lock);
	if (!data->death || ft_strcnmp(message, "died", 4) == 0)
		printf("%ld %d %s\n", get_current_time() - data->start_time, data->philo[i].id, message);
	pthread_mutex_unlock(&data->msg_lock);
}

void	*monitoring(void *arg)
{
	t_data *m;
	int		i;
	bool	all_full;

	m = arg;
	i = 0;
	all_full = true;
	while (!m->death)
	{
		while (i < m->philo_no)
		{
			if (get_current_time() - m->philo[i].time_eaten > m->die_ti)
			{
				m->death = true;
				print_message(&m, "died", i);
				return (NULL);
			}
			i++;
		}
		if (m->eat_no > 0)
		{
			i = 0;
			while (i < m->philo_no)
			{
				if (m->philo[i].meals_eaten < m->eat_no)
					all_full = false;
				i++;
			}
			if (all_full)
			{
				m->death = true;
				return (NULL);
			}
			i = 0;
		}
		usleep(1000);
	}
	return (NULL);
}

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_no)
	{
		if (pthread_create(&data->philo[i].philos, NULL, &routine, NULL) != 0)
			return (-1);
		i++;
	}
}

void	init_data(t_data *data, char **av)
{
	int	i;

	i = 0;
	data->philo_no = ft_atoi(av[1]);
	data->die_ti = ft_atoi(av[2]);
	data->eat_ti = ft_atoi(av[3]);
	data->sle_ti = ft_atoi(av[4]);
	if (av[5])
		data->eat_no = ft_atoi(av[5]);
	else
		data->eat_no = 0;
	data->death = false;
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->time_lock, NULL);
	pthread_mutex_init(&data->action_lock, NULL);
	pthread_mutex_init(&data->upd_lock, NULL);
	pthread_mutex_init(&data->msg_lock, NULL);
	get_time(data);
	data->philo = malloc(sizeof(t_philo) * data->philo_no);
	if (!data->philo)
		return (0);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_no);
	if (!data->fork)
		return (0);
	while (i < data->philo_no)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		data->philo[i].meals_eaten = 0;
		data->philo[i].time_eaten = 0;
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = i + 1;
		if (i + 1 < data->philo_no)
			data->philo[i].right_fork = i + 2;
		else
			data->philo[i].right_fork = 1;
		i++;
	}
}
