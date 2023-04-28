#@copyright : AhmedOSA

CC=arm-none-eabi-
CFLAGS=-g -mcpu=arm926ej-s
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
Project_name=LEARN_IN_DEPTH


all: $(Project_name).bin
	@echo "========Build is Done========="
		
startup.o: startup.s
	$(CC)as.exe $(CFLAGS) $< -o $@
	
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@
	
	
$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld.txt $(LIBS) $(OBJ) $(ASOBJ) -o $(Project_name).elf
	
$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@
	
clean_all:
	rm *.o *.elf *.bin	
	
clean:
	rm *.elf *.bin
	