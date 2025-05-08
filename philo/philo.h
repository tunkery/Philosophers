/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolcay <bolcay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:47:32 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/08 20:19:20 by bolcay           ###   ########.fr       */
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

// typedef struct	s_philo
// {
// 	int			left_fork;
// 	int			right_fork;
// 	int			eat_num;
// 	int			num;
// 	pthread_t	philos;
// }	t_philo;

typedef struct	s_data
{
	int				left_fork;
	int				right_fork;
	int				eat_num;
	int				num;
	pthread_t		philos;
	int				philo_no;
	int				eat_ti;
	int				die_ti;
	int				sle_ti;
	int				eat_no;
	long	long	time;
}	t_data;

int		ft_atoi(const char *str);

void	init_data(t_data *data, char **av);

#endif