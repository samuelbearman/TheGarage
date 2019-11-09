#include <sys/times.h>

clock_t getCurrentCPU(void) {
    struct tms tbuf;

    times(&tbuf);
    // To convert to secs: divide by sysconf(_SC_CLK_TCK)                       
    return tbuf.tms_utime;
}
