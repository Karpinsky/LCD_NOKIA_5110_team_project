################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/i2c.c \
../Src/lcd5110.c \
../Src/lcd5110_hal.c \
../Src/lcd5110_ll.c \
../Src/main.c \
../Src/rng.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c 

OBJS += \
./Src/gpio.o \
./Src/i2c.o \
./Src/lcd5110.o \
./Src/lcd5110_hal.o \
./Src/lcd5110_ll.o \
./Src/main.o \
./Src/rng.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o 

C_DEPS += \
./Src/gpio.d \
./Src/i2c.d \
./Src/lcd5110.d \
./Src/lcd5110_hal.d \
./Src/lcd5110_ll.d \
./Src/main.d \
./Src/rng.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"F:/Workbench Projects/LCD_NOKIA_5110_team_project/Inc" -I"F:/Workbench Projects/LCD_NOKIA_5110_team_project/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/Workbench Projects/LCD_NOKIA_5110_team_project/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/Workbench Projects/LCD_NOKIA_5110_team_project/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/Workbench Projects/LCD_NOKIA_5110_team_project/Drivers/CMSIS/Include" -I"F:/Workbench Projects/LCD_NOKIA_5110_team_project/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


