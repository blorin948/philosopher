#include "philo_three.h"

void	free_all(t_env *s, sem_t *else_dead, t_philo *philo)
{
	int	i;

	i = 0;
	while (s->pid[i])
		kill(s->pid[i++], SIGKILL);
	(void)else_dead;
	free(s->pid);
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

sem_t	*init_semaphore(t_env *s, t_philo *philo)
{
	int					i;
	sem_t				*else_death;

	sem_unlink("/print");
	s->print = sem_open("/print", O_CREAT, 0660, 1);
	init_mutex_fork(s);
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
	s->pid = malloc(sizeof(pid_t) * s->nbT);
	while (i < s->nbT)
	{
		init_philo(&philo[i], s, i);
		i++;
	}
	else_death = init_semaphore(s, philo);
	i = 0;
	while (i < s->nbT)
	{
		s->pid[i] = fork();
		if (s->pid[i] == 0)
			loop(&philo[i]);
		i++;
	}
	sem_wait(else_death);
	free_all(s, else_death, philo);
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
