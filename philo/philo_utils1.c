/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhan <batuhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:11:15 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/13 16:24:04 by batuhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_action(t_data *data, char *message)
{
    bool    death;
    long    c_time;

    pthread_mutex_lock(&data->death_lock);
    death = data->philo->death;
    pthread_mutex_unlock(&data->death_lock);
    if (!death)
    {
        pthread_mutex_lock(&data->action_lock);
        c_time = get_current_time();
        printf("%ld philo number: %d %s\n", c_time, data->philo->id, message);
        pthread_mutex_unlock(&data->action_lock);
    }
}

int ft_usleep(int ms, t_data *data)
{
    bool    death;
    
    while ((get_current_time() - data->start_time) < ms)
    {
        pthread_mutex_lock(&data->death_lock);
        death = data->philo->death;
        if (death)
        {
            pthread_mutex_unlock(&data->death_lock);
            return (-1);
        }
        pthread_mutex_unlock(&data->death_lock);
        usleep(200);
    }
    return (0);
}
