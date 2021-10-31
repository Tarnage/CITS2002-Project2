#include <stdio.h>
#include <sys/time.h>               // declares  gettimeofday()

//  #including a C source file this way usually strongly discouraged
#include "strSHA2.c"

static long microseconds(void)
{
    struct timeval  t;

    gettimeofday( &t, NULL );       // timezone not required
    return (t.tv_sec * 1000000) + t.tv_usec;
}

#define NBYTES      (1<<30)

int main(int argc, char *argv[])
{
    uint8 *data  = malloc( NBYTES );
    if(data) {
        sha256_context  ctx;
        uint8           digest[SHA2_DIGEST_LEN_BYTES];

        for(long nbytes=(1<<10) ; nbytes<=NBYTES ; nbytes *= 4) {
            long t0 = microseconds();
                sha256_starts(&ctx);
                sha256_update(&ctx, data, nbytes);
                sha256_finish(&ctx, digest);
            long t1 = microseconds();
            printf("%12li bytes\t%lims\n", nbytes, (t1 - t0)/1000);
        }
        return 0;
    }
    fprintf(stderr, "cannot malloc %li\n", (long)NBYTES);
    return 1;
}
