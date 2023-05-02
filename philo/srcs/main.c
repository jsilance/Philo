/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/03 00:32:17 by jusilanc         ###   ########.fr       */
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
	// setvbuf(stdout, NULL, _IONBF, 0);
	if (ft_philo_param_init(&philo, argv, argc) == -1)
		return (1);
	philo.philos = ft_philo_create(&philo);
	while (++i < philo.nb_philo)
	{
		philo.philos[i].philos = philo.philos;
		if (pthread_create(&philo.thread_p[i], NULL, ft_philosophe,
				(void *)&philo.philos[i]))
			break ;
		usleep(100);
	}
	i = 0;
	while (i < philo.nb_philo)
		pthread_detach(philo.thread_p[i++]);
	if (ft_watchdog(&philo.death))
		ft_philo_destructor(&philo);
	return (0);
}
