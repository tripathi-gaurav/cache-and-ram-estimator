//Referred the below link
//https://stackoverflow.com/questions/19136846/write-a-program-to-get-cpu-cache-sizes-and-levels/19142024#19142024

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


int main() {
    unsigned int steps = 24 * 1024 * 1024;

    int lengthMod;
    unsigned int i;
    int stride = 64;
    double timeTaken;
    clock_t start;

    int size;

    FILE *fd = fopen("cache.dat","w");
    for (size = 2; size < 24; size++) {
	    lengthMod = pow(2, size) - 1;

      int * arr = (int *)malloc(sizeof(int) * lengthMod);
      int x;
      for (x = 0; x < lengthMod; x++) {
        arr[x] = 1;
      }

	    start = clock();
	    for (i = 0; i < steps; i++) {
        ++arr[ (i * 64) % (lengthMod - 1)];
        /*
        from stackoverflow:
        j*16 (* 4 bytes per int = 64B, one cache line - a classic unit stride for the stream detector),
        with j*64 (4 cache lines). The reason being - the prefetcher can issue 2 prefetches per stream request,
        so it runs ahead of your code when you do unit strides, may still get a bit ahead of you when
        your code is jumping over 2 lines, but become mostly useless with longer jumps (3 isn't good because of your modulu
        */
	    }
	    timeTaken = (double)(clock() - start)/CLOCKS_PER_SEC;
      free(arr);
      printf("%f, %.8f \n", pow(2, size) / 1024, timeTaken);
      fprintf(fd, "%f, %.8f \n", pow(2, size) / 1024, timeTaken);
    }

    return 0;
}
