CFLAGS_hello.o := -DDEBUG

ifeq (${KDIR},)
	KDIR := /lib/modules/$(shell uname -r)/build
endif
obj-m +=hello.o


all:
	make -C ${KDIR} M=$(shell pwd) modules

clean:
	make -C ${KDIR} M=$(shell pwd) clean
