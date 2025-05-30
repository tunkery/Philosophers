/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:47:32 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/30 14:25:55 by bolcay           ###   ########.fr       */
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
	long		start_time;
	pthread_mutex_t	state_mutex;
	pthread_t	philos;
	pthread_mutex_t	fork_lock;
	struct s_data	*data;
}	t_philo;

typedef struct	s_data
{
	t_philo			*philo;
	pthread_t		monitor;
	int				eat_ti;
	int				die_ti;
	int				sle_ti;
	int				philo_no;
	int				eat_no;
	long			start_time;
	struct timeval	start;
	long	long	time;
	bool			death;
	pthread_mutex_t	*fork;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	msg_lock;
}	t_data;

int		ft_atoi(const char *str);
long	get_current_time(void);
void	get_time(t_data *data);
int		ft_strlen(const char *str);

void	init_data(t_data *data, char **av);
int		check_args(char **av);

void	*routine(void *args);

int 	ft_usleep(int ms, t_data *data);

int		philo_action(t_philo *philo, char *message);

void	create_philos(t_data *data);
int		philos_eat(t_philo *philo);
int		beginning_of_eat(t_philo *philo);
int		philos_be_eatin(t_philo *philo);
int		eat(t_philo *philo, char *message);
int		thinking(t_philo *philo, char *message);
int		sleepin(t_philo *philo, char *message);
int		unlock_and_return(t_philo *philo);
void	*monitoring(void *args);
void	clean_up(t_data *data);
void	print_message(t_philo *philo, char *message);
int	ft_strncmp(const char *s1, const char *s2, size_t c);
// void	philo_sleep(t_philo *philo, char *message);

#endif