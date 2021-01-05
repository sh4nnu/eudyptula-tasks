ifeq (${KDIR},)
	KDIR := /lib/modules/$(shell uname -r)/build 
endif
obj-m +=hello.o
#@echo "in if" ${KDIR}



#@echo "out if" ${KDIR}
all:
	@echo "KDIR =" ${KDIR}
	make -C ${KDIR} M=$(shell pwd) modules

clean: 
	make -C ${KDIR} M=$(shell pwd) clean
