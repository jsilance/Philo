/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/08 10:04:39 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static int	ft_watchdog(t_philo_param *philo)
{
	int	ret;

	ret = 0;
	while (1)
	{
		if (pthread_mutex_lock(&philo->mut_dead))
			break ;
		if (philo->death == 1)
			ret = 1;
		pthread_mutex_unlock(&philo->mut_dead);
		if (ret == 1)
			break ;
		usleep(100);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo_param	philo;
	int				i;

	i = -1;
	if (ft_philo_param_init(&philo, argv, argc) == -1)
		return (1);
	philo.philos = ft_philo_create(&philo, 0);
	while (++i < philo.nb_philo && philo.philos)
	{
		philo.philos[i].philos = philo.philos;
		if (pthread_create(&philo.thread_p[i], NULL, ft_philosophe,
				(void *)&philo.philos[i]))
			break ;
	}
	i = 0;
	while (i < philo.nb_philo && philo.nb_to_eat != -1 && philo.philos)
		if (pthread_join(philo.thread_p[i++], NULL))
			return (ft_philo_destructor(&philo, 1));
	while (i < philo.nb_philo && philo.nb_to_eat == -1 && philo.philos)
		if (pthread_detach(philo.thread_p[i++]))
			return (ft_philo_destructor(&philo, 1));
	if (philo.philos && philo.nb_to_eat == -1 && ft_watchdog(&philo))
		i = 0;
	return (ft_philo_destructor(&philo, (!philo.philos)));
}
