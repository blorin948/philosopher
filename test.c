#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

/*
** Returns the timestamp in milliseconds
*/

long    get_time(void)
{
    struct timeval  tp;
    long            milliseconds;

    gettimeofday(&tp, NULL);
    milliseconds = tp.tv_sec * 1000;
    milliseconds += tp.tv_usec / 1000;
    return (milliseconds);
}

/*
** Prints time, sleeps 200ms, repeats!
*/

void use_sleep(int time)
{
	int k = time/4;

	usleep(k);
	usleep(k);
	usleep(k);
	usleep(k);
}

int main(void)
{
    long start_time;
		
		// Remember when we started
    start_time = get_time();

    while (1)
    {
				// Print time from start, in ms
        printf("%ld\n", get_time() - start_time);

				// Sleep 200 times 1000 microseconds (1 millisecond)
		
        use_sleep(200 * 1000);
    }
}