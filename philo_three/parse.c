#include "philo_three.h"

int	parse_start(int ac, char **av, t_env *s)
{
	int	i;

	i = 1;
	gettimeofday(&s->time, NULL);
	while (i < ac)
	{
		if (ft_isdigit(av[i]) == 0)
			return (0);
		i++;
	}
	if (ac == 6)
	{
		s->nbT_eat = ft_atoi(av[5]);
		if (s->nbT_eat == 0)
			return (0);
	}
	else
		s->nbT_eat = 0;
	s->nbT = ft_atoi(av[1]);
	s->time_die = ft_atoi(av[2]);
	s->time_eat = ft_atoi(av[3]);
	s->time_sleep = ft_atoi(av[4]);
	s->time_start = (1000000 * s->time.tv_sec + s->time.tv_usec) / 1000;
	s->nb_eat = 0;
	return (1);
}
