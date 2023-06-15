/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:48:08 by juzheng           #+#    #+#             */
/*   Updated: 2023/06/15 16:48:09 by juzheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	use_two_forks(t_philo *philo, t_data *info)
{
	pthread_mutex_lock(&(info->fork
		[ft_check_fork(philo->left, philo->right)]));
	terminal_msg(info, philo->id, "has taken fork");
	if (info->nbr_philo != 1)
	{
		pthread_mutex_lock(&(info->fork
			[ft_check_fork01(philo->right, philo->left)]));
		terminal_msg(info, philo->id, "has taken fork");
		terminal_msg(info, philo->id, "is eating");
		pthread_mutex_lock(&info->mutex);
		philo->last_eat = ft_time_in_ms();
		pthread_mutex_unlock(&info->mutex);
		philo->eat_count = philo->eat_count + 1;
		pause_time(info, (long long)info->eat_time);
		pthread_mutex_unlock(&(info->fork
			[ft_check_fork01(philo->right, philo->left)]));
	}
	pthread_mutex_unlock(&(info->fork
		[ft_check_fork(philo->left, philo->right)]));
}

void	terminal_msg(t_data *info, int id, char *message)
{
	long long	now;

	now = ft_time_in_ms();
	pthread_mutex_lock(&(info->lock));
	if (!(info->finished))
	{
		printf("%lld ", (now - info->time_of_start));
		printf("%d ", id + 1);
		printf("%s\n", message);
	}
	pthread_mutex_unlock(&(info->lock));
}

void	sleep_and_think(t_philo *philo, t_data *info)
{
	terminal_msg(info, philo->id, "is sleeping");
	pause_time(info, (long long)info->sleep_time);
	terminal_msg(info, philo->id, "is thinking");
}

void	pause_time(t_data *info, long long wait_time)
{
	long long	now;
	long long	start;

	start = ft_time_in_ms();
	while (1)
	{
		pthread_mutex_lock(&(info->mutex));
		if (info->finished)
		{
			pthread_mutex_unlock(&(info->mutex));
			break ;
		}
		pthread_mutex_unlock(&(info->mutex));
		now = ft_time_in_ms();
		if ((now - start) >= wait_time)
			break ;
		usleep(10);
	}
}

void	threads_free(t_philo *philo, t_data *info)
{
	int index;

	index = 0;
	while (index < info->nbr_philo)
		pthread_mutex_destroy(&(info->fork[index++]));
	free(philo);
	free(info->fork);
	pthread_mutex_destroy(&(info->lock));
	pthread_mutex_destroy(&(info->mutex));
}