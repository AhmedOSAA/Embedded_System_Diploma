################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Keypad_driver/kaypad.c 

OBJS += \
./HAL/Keypad_driver/kaypad.o 

C_DEPS += \
./HAL/Keypad_driver/kaypad.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Keypad_driver/kaypad.o: ../HAL/Keypad_driver/kaypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/midom/workspace/STM32CubelDE/Drivers/Stm32_F103C6_Drivers/Inc" -I"C:/Users/midom/workspace/STM32CubelDE/Drivers/HAL/Includes" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Keypad_driver/kaypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

