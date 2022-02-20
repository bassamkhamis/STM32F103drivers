#auther  : bassam
# Date   :feb 4- 2022
CC=arm-none-eabi-
CFLAFS=-mcpu=cortex-m3 -gdwarf-2
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
obj= $(SRC:.c=.o)
As=$(wildcard *.s)
objAs=$(As:.s=.o)
project_name=project_one

all: $(project_name).bin

%.o: %.s
	$(CC)as.exe $(CFLAFS) $< -o $@ 2> log
	
	
%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAFS) $< -o $@
	
$(project_name).elf: $(objAs) $(obj)
	$(CC)ld.exe -T linker_script.ld $(objAs) $(obj) -o $@ -Map=Map_file.map

$(project_name).bin: $(project_name).elf 
	$(CC)objcopy.exe $< $@
	@echo "Every thing is Done...."

clean_all:
	rm *.bin *.elf *.o
	
clean:
	rm *.bin *.elf