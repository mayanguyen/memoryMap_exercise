/* 
 * Van Mai Nguyen Thi
 * EOS: Lab 8
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(int argc, char *argv[]) {
    unsigned int t1, t2, period;
    
    volatile unsigned int *gpio_base, *fsel1, *clr0, *gpset0;
    int memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (memfd < 0) {
        perror("unable to open /dev/mem\n");
        exit(-1);
    }
    gpio_base = (unsigned int *) mmap(0, 4096, PROT_WRITE, MAP_SHARED, memfd, 0x20200000);
    
    
    t1 = atoi(argv[0]);
    period = atoi(argv[1]);
    t2 = period-t1;
    
    fsel1 = (unsigned int *)(gpio_base + 2);
    clr0 = (unsigned int *)(gpio_base + 7);
    gpset0 = (unsigned int *)(gpio_base + 10);
    
    close(memfd);
    if (gpio_base == MAP_FAILED) {
        perror("unable to mmap\n");
        exit(-1);
    }
    
    *fsel1 = (1 << 15);
    for (;;){
        *clr0 = (1 << 25);
        usleep(t1);
        *gpset0 = (1 << 25);
        usleep(t2);
    }
    
}

