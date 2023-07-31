################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LCD_driver/lcd.c 

OBJS += \
./HAL/LCD_driver/lcd.o 

C_DEPS += \
./HAL/LCD_driver/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LCD_driver/lcd.o: ../HAL/LCD_driver/lcd.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/midom/workspace/STM32CubelDE/Drivers/Stm32_F103C6_Drivers/Inc" -I"C:/Users/midom/workspace/STM32CubelDE/Drivers/HAL/Includes" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD_driver/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

