/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:44:47 by juzheng           #+#    #+#             */
/*   Updated: 2023/06/12 09:44:48 by juzheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	long long		last_eat;
	int				id;
	int				right;
	int				left;
	int				eat_count;
}			t_philo;

typedef struct s_data
{
	long long		time_of_start;
	int				nbr_philo;
	int				eat_nbr;
	int				sleep_time;
	int				die_time;
	int				eat_time;
	int				finished_eat;
	int				finished;
	int				dead;
	pthread_mutex_t	lock;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
}			t_data;

int			check_input(char **argv, int i, int j);

void		ft_init(t_data *data, char **argv, int argc);

void		use_two_forks(t_philo *philo, t_data *info);
void		pause_time(t_data *info, long long wait_time);
void		sleep_and_think(t_philo *philo, t_data *info);
void		terminal_msg(t_data *info, int id, char *message);

void		ft_philo_threads(t_philo *philo, t_data *data);
void		finished_or_died(t_philo *philo, t_data *data);
void		*routine_philo(void *info);
void		threads_free(t_philo *philo, t_data *info);

int			ft_atoi(const char *str);
void		ft_exit(char *str);
int			ft_strlen(char *str);
long long	ft_time_in_ms(void);
int			ft_check_fork01(int l, int r);
int			ft_check_fork(int l, int r);

#endif
