/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 02:32:58 by jusilanc          #+#    #+#             */
/*   Updated: 2023/04/28 04:27:07 by jusilanc         ###   ########.fr       */
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

int	ft_philo_init(t_philo *philo, char **argv, int argc)
{
	if (first_layer_check(argc) == -1 || second_layer_check(argc, argv) == -1)
		return (-1);
	*philo = (t_philo){ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
		ft_atoi(argv[4]), 0};
	if (argc == 6)
		philo->nb_to_eat = ft_atoi(argv[5]);
	return (0);
}
