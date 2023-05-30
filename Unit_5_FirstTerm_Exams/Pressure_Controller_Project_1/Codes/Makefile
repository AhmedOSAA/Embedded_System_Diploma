#@copyright : ENG.AhmedOsamaa

CC=arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -mthumb -gdwarf-2
INCS=-I .
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
Peoject_name=Pressure_Controller

all: $(Peoject_name).bin
	@echo "============Build is Done=============="

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

$(Peoject_name).elf : $(OBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) -o $@ -Map=Map_file.map

$(Peoject_name).bin : $(Peoject_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin