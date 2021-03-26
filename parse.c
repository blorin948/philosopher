#include "philo_one.h"

int parse_start(int ac, char **av, t_env *s)
{
	gettimeofday(&s->time, NULL);
	int i = 1;
	while (i < ac)
	{
		if (ft_isdigit(av[i]) == 0)
			return (0);
		i++;
	}
	s->nbT = ft_atoi(av[1]);
	s->time_die = ft_atoi(av[2]);
	s->time_eat = ft_atoi(av[3]);
	s->time_sleep = ft_atoi(av[4]);
	s->time_start = (1000000 * s->time.tv_sec + s->time.tv_usec) / 1000;
	return (1);
}