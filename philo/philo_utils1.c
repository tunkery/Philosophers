/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:11:15 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/30 14:03:53 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo *philo, char *message)
{
	t_data	*data;
	bool	check;
	long	time;

	data = philo->data;
	time = 0;
    pthread_mutex_lock(&data->death_lock);
    check = data->death;
    pthread_mutex_unlock(&data->death_lock);
    if (!check)
    {
        time = get_current_time();
        pthread_mutex_lock(&data->state_mutex);
        if (time - philo->time_eaten > data->die_ti)
        {
            pthread_mutex_lock(&data->death_lock);
            data->death = true;
            pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_unlock(&data->state_mutex);
            return (-1);
        }
        printf("%ld %d %s\n",time - data->start_time, philo->id, message);
        pthread_mutex_unlock(&data->state_mutex);
		ft_usleep(100, data);
    }
    return (0);
}

int	sleepin(t_philo *philo, char *message)
{
	t_data	*data;
	bool	check;
	long	time;

	data = philo->data;
	time = 0;
    pthread_mutex_lock(&data->death_lock);
    check = data->death;
    pthread_mutex_unlock(&data->death_lock);
    if (!check)
    {
        time = get_current_time();
        pthread_mutex_lock(&data->state_mutex);
        if (time - philo->time_eaten > data->die_ti)
        {
            pthread_mutex_lock(&data->death_lock);
            data->death = true;
            pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_unlock(&data->state_mutex);
            return (-1);
        }
        printf("%ld %d %s\n",time - data->start_time, philo->id, message);
        pthread_mutex_unlock(&data->state_mutex);
		ft_usleep(data->sle_ti, data);
    }
    return (0);
}

int ft_usleep(int ms, t_data *data)
{
    bool    death;
    long    c_time;
    
    c_time = get_current_time();
    while ((get_current_time() - c_time) < ms)
    {
        pthread_mutex_lock(&data->death_lock);
        death = data->death;
        if (death)
        {
            pthread_mutex_unlock(&data->death_lock);
            return (-1);
        }
        pthread_mutex_unlock(&data->death_lock);
        usleep(100);
    }
    return (0);
}

int	philo_action(t_philo *philo, char *message)
{
    t_data	*data;
    bool	check;
    long	time;

    data = philo->data;
    time = 0;
    pthread_mutex_lock(&data->death_lock);
    check = data->death;
    pthread_mutex_unlock(&data->death_lock);
    if (!check)
    {
        time = get_current_time();
        pthread_mutex_lock(&data->state_mutex);
        if (time - philo->time_eaten > data->die_ti)
        {
            pthread_mutex_lock(&data->death_lock);
            data->death = true;
            pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_unlock(&data->state_mutex);
            return (-1);
        }
        else
            printf("%ld %d %s\n",time - data->start_time, philo->id, message);
        pthread_mutex_unlock(&data->state_mutex);
    }
    return (0);
}

int	eat(t_philo *philo, char *message)
{
    t_data	*data;
    bool	check;
    long	time;

    data = philo->data;
    time = 0;
    pthread_mutex_lock(&data->death_lock);
    check = data->death;
    pthread_mutex_unlock(&data->death_lock);
    if (!check)
    {
        time = get_current_time();
        pthread_mutex_lock(&data->state_mutex);
        if (time - philo->time_eaten > data->die_ti)
        {
            pthread_mutex_lock(&data->death_lock);
            data->death = true;
            pthread_mutex_unlock(&data->death_lock);
			pthread_mutex_unlock(&data->state_mutex);
            return (-1);
        }
        printf("%ld %d %s\n",time - data->start_time, philo->id, message);
		philo->time_eaten = time;
		philo->meals_eaten++;
        pthread_mutex_unlock(&data->state_mutex);
		ft_usleep(data->eat_ti, data);
    }
	return (0);
}

int	unlock_and_return(t_philo *philo)
{
	t_data	*data;
	int		left;
	int		right;

	data = philo->data;
	left = philo->left_fork;
	right = philo->right_fork;
	pthread_mutex_unlock(&data->fork[left]);
	pthread_mutex_unlock(&data->fork[right]);
	return (-1);
}
