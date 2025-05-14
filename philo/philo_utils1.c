/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:11:15 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/14 18:25:05 by bolcay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo, char *message)
{
	t_data *data;
    bool    death;
    long    c_time;

    data = philo->data;
    pthread_mutex_lock(&data->death_lock);
    death = data->death;
    pthread_mutex_unlock(&data->death_lock);
    if (!death)
    {
        pthread_mutex_lock(&data->sleep_lock);
        c_time = get_current_time() - data->start_time;
        printf("%ld %d %s\n", c_time, philo->id, message);
        pthread_mutex_unlock(&data->sleep_lock);
    }
}

void	philo_action(t_philo *philo, char *message)
{
    t_data *data;
    bool    death;
    long    c_time;

    data = philo->data;
    pthread_mutex_lock(&data->death_lock);
    death = data->death;
    pthread_mutex_unlock(&data->death_lock);
    if (!death)
    {
        pthread_mutex_lock(&data->action_lock);
        c_time = get_current_time() - data->start_time;
        printf("%ld %d %s\n", c_time, philo->id, message);
        pthread_mutex_unlock(&data->action_lock);
    }
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
