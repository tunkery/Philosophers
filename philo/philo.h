/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhan <batuhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:47:32 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/11 22:51:09 by batuhan          ###   ########.fr       */
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
	int			num;
	bool		death;
	pthread_t	philos;
	pthread_mutex_t	lock;
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
}	t_data;

int		ft_atoi(const char *str);
long	get_current_time(void);
void	get_time(t_data *data);
int		ft_strlen(const char *str);

void	init_data(t_data *data, char **av);
int		check_args(char **av);

#endif