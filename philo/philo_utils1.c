/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:11:15 by bolcay            #+#    #+#             */
/*   Updated: 2025/06/06 14:15:01 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo *philo, char *message)
{
	t_data	*data;
    bool    check;
	long	time;

	data = philo->data;
	time = 0;
    pthread_mutex_lock(&data->death_lock);
    check = data->death;
    pthread_mutex_unlock(&data->death_lock);
    if (!check)
    {
        pthread_mutex_lock(&data->state_mutex);
        time = get_current_time();
        if (time - philo->time_eaten >= data->die_ti)
        {
			pthread_mutex_unlock(&data->state_mutex);
            return (-1);
        }
        pthread_mutex_unlock(&data->state_mutex);
        pthread_mutex_lock(&data->msg_lock);
        printf("%ld %d %s\n",time - data->start_time, philo->id, message);
        pthread_mutex_unlock(&data->msg_lock);
        ft_usleep(data->thi_ti, data);
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
        pthread_mutex_lock(&data->state_mutex);
        time = get_current_time();
        if (time - philo->time_eaten >= data->die_ti)
        {
			pthread_mutex_unlock(&data->state_mutex);
            return (-1);
        }
        pthread_mutex_unlock(&data->state_mutex);
        pthread_mutex_lock(&data->msg_lock);
        printf("%ld %d %s\n",time - data->start_time, philo->id, message);
		pthread_mutex_unlock(&data->msg_lock);
		if (ft_usleep(data->sle_ti, data) == -1)
			return (-1);
		return (0);
    }
    return (-1);
}

int ft_usleep(int ms, t_data *data)
{
    long    c_time;
    
    c_time = get_current_time();
    while ((get_current_time() - c_time) < ms)
    {
        pthread_mutex_lock(&data->death_lock);
        if (data->death)
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
        pthread_mutex_lock(&data->state_mutex);
        time = get_current_time();
        if (time - philo->time_eaten >= data->die_ti)
        {
			pthread_mutex_unlock(&data->state_mutex);
            return (-1);
        }
        pthread_mutex_unlock(&data->state_mutex);
        pthread_mutex_lock(&data->msg_lock);
        printf("%ld %d %s\n",time - data->start_time, philo->id, message);
		pthread_mutex_unlock(&data->msg_lock);
		return (0);
    }
    return (-1);
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
        pthread_mutex_lock(&data->state_mutex);
        time = get_current_time();
        if (time - philo->time_eaten >= data->die_ti)
        {
			pthread_mutex_unlock(&data->state_mutex);
            return (-1);
        }
        philo->meals_eaten++;
        philo->time_eaten = time;
		pthread_mutex_unlock(&data->state_mutex);
		pthread_mutex_lock(&data->msg_lock);
        printf("%ld %d %s\n",time - data->start_time, philo->id, message);
		pthread_mutex_unlock(&data->msg_lock);
		if (ft_usleep(data->eat_ti, data) == -1)
			return (-1);
		return (0);
    }
	return (-1);
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
