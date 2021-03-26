#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


void *salut(void *ok)
{
	usleep(100);
	printf("lol\n");
}

int main()
{
	int i = 0;
	pthread_t philo;
	pthread_create(&philo, NULL, salut, NULL);
	//pthread_detach(philo);
	//pthread_join(philo, NULL);
i++;
i++;
}