/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/23 13:27:03 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static int	ft_watchdog(t_philo_param *philo)
{
	int	ret;

	ret = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->mut_dead);
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
	philo.philos = ft_philo_create(&philo);
	while (++i < philo.nb_philo)
	{
		philo.philos[i].philos = philo.philos;
		if (pthread_create(&philo.thread_p[i], NULL, ft_philosophe,
				(void *)&philo.philos[i]))
			break ;
	}
	i = 0;
	while (i < philo.nb_philo && philo.nb_to_eat != -1)
		pthread_join(philo.thread_p[i++], NULL);
	while (i < philo.nb_philo && philo.nb_to_eat == -1)
		pthread_detach(philo.thread_p[i++]);
	if (philo.nb_to_eat == -1 && ft_watchdog(&philo))
		i = 0;
	ft_philo_destructor(&philo);
	return (0);
}
