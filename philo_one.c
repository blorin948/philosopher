#include "philo_one.h"

int main(int ac, char **av)
{
	t_env *s;
	if (!(s = malloc(sizeof(t_env))))
		return (0);
	if (ac != 5 && ac != 6)
		return (error_return("wrong numbers of arguments"));
	if (parse_start(ac, av, s) == 0)
		return (error_return("error with arguements"));
	int i = 0;
	t_philo *philo;
	philo = malloc(sizeof(t_philo) * s->nbT);
	while (i < s->nbT)
	{
		init_philo(&philo[i], s, i);
		i++;
	}
	i = 0;
	int a = 0;
	while (i < s->nbT)
	{
		while (a < philo[i].info->fork[a])
		{

		}
	}
	start_loop(s);
}