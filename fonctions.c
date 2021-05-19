#include "philo_one.h"

int	error_return(char *str)
{
	printf("%s\n", str);
	return (0);
}

void	my_usleep(int time)
{
	struct timeval	t;
	struct timeval	act;
	long			mili;
	long			curr_mili;

	gettimeofday(&t, NULL);
	mili = (1000000 * t.tv_sec + t.tv_usec + time) / 1000;
	gettimeofday(&act, NULL);
	curr_mili = (1000000 * act.tv_sec + act.tv_usec) / 1000;
	while (curr_mili < mili)
	{
		usleep(50);
		gettimeofday(&act, NULL);
		curr_mili = (1000000 * act.tv_sec + act.tv_usec) / 1000;
	}
}

int	ft_atoi(const char *nptr)
{
	int				i;
	int				signe;
	long long		nb;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == ' '))
		i++;
	signe = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	nb = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * signe);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	print_state(t_philo *s, char *str)
{
	pthread_mutex_lock(s->info->print);
	gettimeofday(&s->info->time, NULL);
	printf("%ld		Philo number %d %s\n", ((1000000 * s->info->time.tv_sec \
	+ s->info->time.tv_usec) / 1000) - s->info->time_start, s->nb, str);
	pthread_mutex_unlock(s->info->print);
}
