#include "philo_one.h"

void	free_all(t_env *s, pthread_mutex_t *else_dead, t_philo *philo)
{
	int	i;

	i = 0;
	free(s->fork);
	pthread_mutex_unlock(else_dead);
	pthread_mutex_destroy(else_dead);
	free(else_dead);
	free(philo);
	free(s->pthread);
	while (i < s->nbT)
		pthread_mutex_unlock(&s->fork_m[i++]);
	i = 0;
	while (i < s->nbT)
		pthread_mutex_destroy(&s->fork_m[i++]);
	free(s->fork_m);
	pthread_mutex_destroy(s->print);
	free(s->print);
	free(s);
}

void	init_mutex_fork(t_env *s)
{
	int	i;

	i = 0;
	s->fork_m = malloc(sizeof(pthread_mutex_t) * s->nbT);
	while (i < s->nbT)
	{
		pthread_mutex_init(&s->fork_m[i], NULL);
		i++;
	}
}

pthread_mutex_t	*init_mutex_death(t_env *s, t_philo *philo)
{
	int					i;
	pthread_mutex_t		*else_death;

	i = 0;
	else_death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(else_death, NULL);
	pthread_mutex_lock(else_death);
	while (i < s->nbT)
	{
		philo[i].else_death = else_death;
		i++;
	}
	return (else_death);
}

void	start_init(t_env *s)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*else_death;

	i = 0;
	philo = malloc(sizeof(t_philo) * s->nbT);
	init_mutex_fork(s);
	while (i < s->nbT)
	{
		init_philo(&philo[i], s, i);
		i++;
	}
	else_death = init_mutex_death(s, philo);
	s->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(s->print, NULL);
	start_loop(s, philo);
	pthread_mutex_lock(else_death);
}

int	main(int ac, char **av)
{
	t_env	*s;

	s = malloc(sizeof(t_env));
	init_env(s);
	if (ac != 5 && ac != 6)
		return (error_return("wrong numbers of arguments", s));
	if (parse_start(ac, av, s) == 0)
		return (error_return("error with arguments", s));
	if (s->nbT == 0)
		return (error_return("error with arguments", s));
	init_env2(s);
	start_init(s);
}
