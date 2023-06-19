/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzheng <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:44:55 by juzheng           #+#    #+#             */
/*   Updated: 2023/06/12 09:44:56 by juzheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
				return (1);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		if (argc < 5)
			ft_exit("At least 5 arguments are needed\n");
		else if (argc > 6)
			ft_exit("only 6 arguments are needed\n");
	}
	if (check_input(argv, 0, 1) != 0)
		ft_exit("Invalid Arguments\n");
	memset(&data, 0, sizeof(t_data));
	ft_init(&data, argv, argc);
}
