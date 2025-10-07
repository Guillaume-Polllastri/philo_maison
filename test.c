#include <stdio.h>
#include <sys/time.h>

int	main()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("tvsec: %ld\n", tv.tv_sec);
	printf("tvusec: %ld\n", tv.tv_usec);
}