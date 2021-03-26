#include "philo_one.h"

int error_return(char *str)
{
	printf("%s\n", str);
	return (0);
}

int		ft_atoi(const char *nptr)
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

int		ft_isdigit(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

long get_time(long old_time)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	long new_time = (1000000 * time.tv_sec + time.tv_usec) / 1000;
	return (new_time - old_time);
}