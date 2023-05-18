/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 02:32:58 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/17 18:08:16 by jusilanc         ###   ########.fr       */
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
	*philo = (t_philo_param){ft_atoi(argv[1]), ft_atoi(argv[2]),
		ft_atoi(argv[3]), ft_atoi(argv[4]), -1, NULL, NULL, {0}, 0};
	if (argc == 6)
		philo->nb_to_eat = ft_atoi(argv[5]);
	if (philo->nb_philo < 1)
		return (-1);
	philo->thread_p = (pthread_t *)malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!philo->thread_p)
		return (-1);
	pthread_mutex_init(&philo->printing, NULL);
	return (0);
}
