/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:47:32 by bolcay            #+#    #+#             */
/*   Updated: 2025/06/20 06:37:04 by bolcay           ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long			time_eaten;
	long			start_time;
	pthread_t		philos;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_t		monitor;
	int				thi_ti;
	int				eat_ti;
	int				die_ti;
	int				sle_ti;
	int				philo_no;
	int				eat_no;
	long			start_time;
	bool			death;
	pthread_mutex_t	*fork;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	msg_lock;
}	t_data;

// Helper functions

int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t c);
int		ft_strlen(const char *str);
int		ft_usleep(int ms, t_data *data);
int		check_args(char **av);
long	get_current_time(void);
void	print_message(t_philo *philo, char *message, int i);
bool	death_check(t_philo *philo);
int		print_for_eat(t_philo *philo, char *message, long time);

// Initialize everything

int		init_data(t_data *data);
int		init_arguments(t_data *data, char **av);
void	create_philos(t_data *data);

// Philo actions

void	*routine(void *args);
void	*monitoring(void *args);
int		beginning_of_eat(t_philo *philo);
int		philos_be_eatin(t_philo *philo);
int		philo_action(t_philo *philo, char *message);
int		eat(t_philo *philo, char *message);
int		thinking(t_philo *philo, char *message);
int		sleepin(t_philo *philo, char *message);

// Clean-up
void	clean_up(t_data *data);

#endif