CROSS_COMPILE 	?= /etc/arm/7.5.0/bin/arm-linux-gnueabihf-
TARGET		  	?= uart

CC 				:= $(CROSS_COMPILE)gcc
LD				:= $(CROSS_COMPILE)ld
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP 		:= $(CROSS_COMPILE)objdump


LIBPATH			:= -L /etc/arm/7.5.0/lib/gcc/arm-linux-gnueabihf/7.5.0/ -lgcc
																			
SRCDIRS := $(shell find . -type f -name "*.S" -exec dirname {} \; | sort -u)
CRCDIRS := $(shell find . -type f -name "*.c" -exec dirname {} \; | sort -u)
INCDIRS := $(shell find . -type f -name "*.h" -exec dirname {} \; | sort -u)

INCLUDE			:= $(patsubst %, -I %, $(INCDIRS))
SFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES			:= $(foreach dir, $(CRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR		:= $(notdir  $(SFILES))
CFILENDIR		:= $(notdir  $(CFILES))

SOBJS			:= $(patsubst %, build/%, $(SFILENDIR:.S=.o))
COBJS			:= $(patsubst %, build/%, $(CFILENDIR:.c=.o))
OBJS			:= $(SOBJS) $(COBJS)

VPATH			:= $(SRCDIRS) $(CRCDIRS)
CFLAGES			:= -Wall
CPPFLAGS   		:= -nostdlib -fno-builtin 
#-std=c99 -march=armv7-a -mfpu=vfp3 -Os -g

$(TARGET).bin : $(OBJS)
	$(LD) -Ttools/imx6ull.lds -o $(TARGET).elf $^ $(LIBPATH) 
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis
	tools/mkimage -n tools/imximage.cfg.cfgtmp -T imximage -e 0x87800000 -d $(TARGET).bin $(TARGET).imx
	dd if=/dev/zero of=tools/1k.bin bs=1024 count=1
	cat tools/1k.bin $(TARGET).imx > $(TARGET).img

$(SOBJS) : build/%.o : %.S
	$(CC) $(CFLAGES) $(CPPFLAGS) -c -O2  $(INCLUDE) -o $@ $<

$(COBJS) : build/%.o : %.c
	$(CC) $(CFLAGES) -Wa,-mimplicit-it=thumb $(CPPFLAGS) -c -O2  $(INCLUDE) -o $@ $<

run:
	sudo uuu ./$(TARGET).imx /dev/hidraw1
	
.PHONY: clean	
clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(TARGET).img $(TARGET).imx $(COBJS) $(SOBJS)

download:
	make clean
	make -j4
	make run