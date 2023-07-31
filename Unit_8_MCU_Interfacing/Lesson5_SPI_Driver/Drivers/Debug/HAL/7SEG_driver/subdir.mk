################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/7SEG_driver/7SEG.c 

OBJS += \
./HAL/7SEG_driver/7SEG.o 

C_DEPS += \
./HAL/7SEG_driver/7SEG.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/7SEG_driver/7SEG.o: ../HAL/7SEG_driver/7SEG.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/midom/workspace/STM32CubelDE/Drivers/Stm32_F103C6_Drivers/Inc" -I"C:/Users/midom/workspace/STM32CubelDE/Drivers/HAL/Includes" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/7SEG_driver/7SEG.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

