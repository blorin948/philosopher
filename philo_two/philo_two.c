#include "philo_two.h"

void	free_all(t_env *s, sem_t *else_dead, t_philo *philo)
{
	int	i;

	i = 0;
	(void)else_dead;
	sem_close(s->fork);
	sem_close(else_dead);
	free(philo);
	free(s->pthread);
	sem_close(s->print);
	free(s);
}

void	init_mutex_fork(t_env *s)
{
	sem_unlink("/fork");
	s->fork = sem_open("/fork", O_CREAT, 0660, s->nbT);
}

sem_t	*init_mutex_death(t_env *s, t_philo *philo)
{
	int					i;
	sem_t				*else_death;

	i = 0;
	sem_unlink("/death");
	else_death = sem_open("/death", O_CREAT, 0660, 0);
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
	sem_t			*else_death;

	i = 0;
	philo = malloc(sizeof(t_philo) * s->nbT);
	init_mutex_fork(s);
	while (i < s->nbT)
	{
		init_philo(&philo[i], s, i);
		i++;
	}
	else_death = init_mutex_death(s, philo);
	sem_unlink("/print");
	s->print = sem_open("/print", O_CREAT, 0660, 1);
	start_loop(s, philo);
	sem_wait(else_death);
}

int	main(int ac, char **av)
{
	t_env	*s;

	s = malloc(sizeof(t_env));
	init_env(s);
	if (ac != 5 && ac != 6)
	{
		free(s);
		return (error_return("wrong numbers of arguments"));
	}
	if (parse_start(ac, av, s) == 0)
	{
		free(s);
		return (error_return("error with arguments"));
	}
	if (s->nbT == 0)
	{
		free(s);
		return (error_return("error with arguments"));
	}
	init_env2(s);
	start_init(s);
}
