/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/04/29 01:57:35 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

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
	while (i < philo.nb_philo)
		pthread_join(philo.thread_p[i++], NULL);
	ft_philo_destructor(&philo);
	return (0);
}
