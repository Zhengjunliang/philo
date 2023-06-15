/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:28:46 by juzheng           #+#    #+#             */
/*   Updated: 2023/06/12 11:28:47 by juzheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].last_eat = ft_time_in_ms();
		pthread_create(&(philo[i].thread), NULL, routine_philo, &(philo[i]));
		i++;
	}
	finished_or_died(philo, data);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	threads_free(philo, data);
}

void	priority_check(t_philo *philo)
{
	if (philo->id % 2)
		usleep(1500);
	else
		usleep(800);
}

int	check_finished(t_data *data)
{
	pthread_mutex_lock(&(data->mutex));
	if (data->finished == 1)
	{
		pthread_mutex_unlock(&(data->mutex));
		return (1);
	}
	pthread_mutex_unlock(&(data->mutex));
	return (0);
}

int	finishing_eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&(data->mutex));
	if (data->nbr_2_eat != 0 && philo->eat_count == data->nbr_2_eat)
	{
		data->finished_eat++;
		if (data->finished_eat == data->nbr_philo)
		{
			pthread_mutex_lock(&(data->lock));
			data->finished = 1;
			pthread_mutex_unlock(&(data->lock));
			pthread_mutex_unlock(&(data->mutex));
			return (1);
		}
	}
	pthread_mutex_unlock(&(data->mutex));
	return (0);
}

void	*routine_philo(void *info)
{
	t_data *data;
	t_philo	*philo;

	philo = info;
	data = philo->info;
	priority_check(philo);
	while (1)
	{
		if (check_finished(data) == 1)
			break ;
		use_two_forks(philo, data);
		if (data->nbr_philo == 1)
			finished_or_died(philo, data);
		if (finishing_eating(philo, data) == 1)
			break ;
		sleep_and_think(philo, data);
	}
	return ((void *)0);
}