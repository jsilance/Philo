/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 02:32:58 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/23 15:44:02 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static int	first_layer_check(int argc)
{
	if (argc > 6 || argc < 5)
	{
		printf("Invalid number of arguments\n");
		return (-1);
	}
	return (0);
}

static int	second_layer_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_str_isdigit(argv[i++]))
		{
			printf("Invalid arguments\n");
			return (-1);
		}
	}
	return (0);
}

int	ft_philo_param_init(t_philo_param *philo, char **argv, int argc)
{
	if (first_layer_check(argc) == -1 || second_layer_check(argc, argv) == -1)
		return (-1);
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->nb_to_eat = -1;
	philo->philos = NULL;
	philo->death = 0;
	if (argc == 6)
		philo->nb_to_eat = ft_atoi(argv[5]);
	if (philo->nb_philo < 1)
		return (-1);
	philo->thread_p = (pthread_t *)malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!philo->thread_p)
		return (-1);
	if (pthread_mutex_init(&philo->printing, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&philo->mut_dead, NULL) == -1)
	{
		pthread_mutex_destroy(&philo->printing);
		return (-1);
	}
	return (0);
}
