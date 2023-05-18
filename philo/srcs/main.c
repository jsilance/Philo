/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/18 15:37:12 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_watchdog(int *ptr)
{
	while (1)
	{
		if (*ptr == 1)
			return (1);
		usleep(100);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_param	philo;
	int				i;

	i = -1;
	setvbuf(stdout, NULL, _IONBF, 0);
	if (ft_philo_param_init(&philo, argv, argc) == -1)
		return (1);
	philo.philos = ft_philo_create(&philo);
	while (++i < philo.nb_philo)
	{
		philo.philos[i].philos = philo.philos;
		if (pthread_create(&philo.thread_p[i], NULL, ft_philosophe,
				(void *)&philo.philos[i]))
			break ;
		ft_sleep(philo.time_to_eat + 1);
	}
	i = 0;
	while (i < philo.nb_philo && philo.nb_to_eat != -1)
		pthread_join(philo.thread_p[i++], NULL);
	while (i < philo.nb_philo && philo.nb_to_eat == -1)
		pthread_detach(philo.thread_p[i++]);
	if (philo.nb_to_eat == -1 && ft_watchdog(&philo.death))
		i = 0;
	ft_philo_destructor(&philo);
	return (0);
}
