#include "philo_one.h"

void *loop(void *arg)
{
	t_env *s = (struct s_env *)arg;
	if (s->i == 2)
		s->fork[2] = 0;
	int i = 0;
	/*while (i < s->nbT)
	{
		printf("FORK %d\n", s->fork[i]);
		i++;
	}*/
	printf("%d\n", s->i);
}

void start_loop(t_env *s)
{
	int i;

	i = 0;
	while (s->i < s->nbT)
	{
		pthread_create(&s->pthread[s->i], NULL, loop, (void*)s);
		pthread_detach(s->pthread[s->i]);
		s->i++;
	}

}