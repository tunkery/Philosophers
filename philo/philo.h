/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhan <batuhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:47:32 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/12 16:42:24 by batuhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

typedef struct	s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			meals_eaten;
	long			time_eaten;
	bool		death;
	pthread_t	philos;
	pthread_mutex_t	fork_lock;
}	t_philo;

typedef struct	s_data
{
	t_philo			*philo;
	int				eat_ti;
	int				die_ti;
	int				sle_ti;
	int				philo_no;
	int				eat_no;
	long			start_time;
	struct timeval	start;
	long	long	time;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	action_lock;
}	t_data;

int		ft_atoi(const char *str);
long	get_current_time(void);
void	get_time(t_data *data);
int		ft_strlen(const char *str);

void	init_data(t_data *data, char **av);
int		check_args(char **av);

void	*routine(void *args, t_data *data);

int 	ft_usleep(int ms, t_data *data);

#endif