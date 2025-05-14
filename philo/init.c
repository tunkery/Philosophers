/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:51:35 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/14 13:38:19 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t c)
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

static void	print_message(t_philo *philo, char *message, int i)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->msg_lock);
	if (!data->death || ft_strncmp(message, "died", 4) == 0)
		printf("%ld %d %s\n", get_current_time() - data->start_time, data->philo[i].id, message);
	pthread_mutex_unlock(&data->msg_lock);
}

void	*monitoring(void *arg)
{
	t_philo *m;
	t_philo *p;
	t_data	*data;
	int		i;
	int		full_count;

	m = arg;
	data = m->data;
	i = 0;
	full_count = 0;
	while (!data->death)
	{
		i = 0;
		full_count = 0;
		while (i < data->philo_no)
		{
			p = &data->philo[i];
			pthread_mutex_lock(&data->death_lock);
			if ((get_current_time() - p->time_eaten)> data->die_ti)
			{
				data->death = true;
				print_message(p, "died", i);
				pthread_mutex_unlock(&data->death_lock);
				return (NULL);
			}
			if (data->eat_no > 0 && p->meals_eaten >= data->eat_no)
				full_count++;
			pthread_mutex_unlock(&data->death_lock);
			i++;
		}
		if (data->eat_no > 0 && full_count == data->philo_no)
		{
			pthread_mutex_lock(&data->death_lock);
			data->death = true;
			pthread_mutex_unlock(&data->death_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
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
	pthread_mutex_init(&data->time_lock, NULL);
	pthread_mutex_init(&data->action_lock, NULL);
	pthread_mutex_init(&data->upd_lock, NULL);
	pthread_mutex_init(&data->msg_lock, NULL);
	data->start_time = get_current_time();
	// get_time(data);
	data->philo = malloc(sizeof(t_philo) * data->philo_no);
	if (!data->philo)
		return ;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_no);
	if (!data->fork)
		return ;
	while (i < data->philo_no)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		data->philo[i].data = data;
		data->philo[i].meals_eaten = 0;
		data->philo[i].time_eaten = data->start_time;
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = i;
		if (i + 1 < data->philo_no)
			data->philo[i].right_fork = (i + 1) % data->philo_no;
		else
			data->philo[i].right_fork = 0;
		i++;
	}
}
