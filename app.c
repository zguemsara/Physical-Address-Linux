#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/mman.h>

#define DBFS_FILE_PATH  "/sys/kernel/debug/paddr/output"
#define PADDR   0xff000

struct packet {
        pid_t pid;
        unsigned long vaddr;
        unsigned long paddr;
};
char global[1024*1024];

int main(void)
{



static int a=100;
    int b;
    char *ptr = malloc(1024*1024);
    
    printf("hello, world\n");



    printf(" address of main: %p\n", main);

    printf(" address of b: %p\n", &b );
    printf(" address of a: %p\n", &a );
    printf(" address of global : %p\n", global );
    printf(" address of mem[ptr] : %p\n", ptr);
    printf(" address of printf: %p\n", printf);
    printf(" address of ptrP: %p\n", &ptr); 
    
    
    
    
        int fd, mem, ret;
        struct packet pckt;
	unsigned long vaddr[7];
	
	vaddr[0] = main; 
	vaddr[1] = &b;
	vaddr[2] = &a;
	vaddr[3] = global;
	vaddr[4] = ptr;
	vaddr[5] = printf;
	vaddr[6] = &ptr;
	
	
	
        mem = open("/dev/mem", O_RDWR);

        pckt.pid = getpid();
        
        

        
        for(int i = 0 ; i < 7; i++ )
        {
        pckt.vaddr = vaddr[i];
        pckt.paddr = 0;

        fd = open(DBFS_FILE_PATH, O_RDWR);

        if (fd < 0) {
                printf("debugfs file open error\n");
                exit(-1);
        }

        ret = read(fd, &pckt, sizeof(struct packet));

        if (ret < 0) {
                printf("debugfs input file write failed\n");
                exit(-1);
        }

	printf("%p / %p \n" ,pckt.vaddr, pckt.paddr);
	
	
        

        close(fd);
	}
        munmap((void*)pckt.vaddr, sizeof(unsigned long));
        

        return 0;
}
