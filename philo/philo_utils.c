/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhan <batuhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:03:30 by bolcay            #+#    #+#             */
/*   Updated: 2025/05/13 19:58:00 by batuhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	check;
	int	result;

	result = 0;
	i = 0;
	check = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			check *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * check);
}

void	get_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->start = time;
}

long	get_current_time(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static int	ft_isalpha(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= 97 && str[i] <= 122) && !(str[i] >= 65 && str[i] <= 90))
			return (-1);
		i++;
	}
	return (0);
}

int	check_args(char **av)
{
	if (ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
		return (-1);
	if (ft_isalpha(av[1]) == -1 || ft_isalpha(av[2]) == -1 || ft_isalpha(av[3]) == -1 || ft_isalpha(av[4]) == -1)
		return (-1);
	if (av[5])
	{
		if (ft_atoi(av[5]) < 0)
			return (-1);
		if (ft_isalpha(av[5]) == -1)
			return (-1);
	}
	return (0);
}
