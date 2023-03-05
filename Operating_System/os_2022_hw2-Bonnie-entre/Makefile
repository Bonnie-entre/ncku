
TARGET_MODULE := My_proc

obj-m := $(TARGET_MODULE).o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: 
	gcc -o MT_matrix MT_matrix.c -lpthread

	$(MAKE) -C $(KDIR) M=$(PWD) modules

unload:
	sudo rmmod $(TARGET_MODULE) || true >/dev/null

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

check: all
	$(MAKE) unload
	$(MAKE) load
	./MT_matrix
	$(MAKE) unload


load:
	gcc -o MT_matrix MT_matrix.c -lpthread
	$(MAKE) -C $(KDIR) M=$(PWD) modules	
	sudo insmod $(TARGET_MODULE).ko
	dmesg | tail

exeMT:
	./MT_matrix 2 ./Test_case_1/m1 ./Test_case_1/m2

debug:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	sudo rmmod $(TARGET_MODULE) || true >/dev/null
