obj-m += paddr.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o app app.c;
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
	sudo dmesg -C
	sudo insmod paddr.ko
	sudo rmmod paddr.ko
	dmesg
