################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/adc_dma.c \
../src/dma.c \
../src/exti.c \
../src/flash.c \
../src/gpio.c \
../src/main.c \
../src/max7301.c \
../src/nvic.c \
../src/rcc.c \
../src/spi.c \
../src/spi_dma.c \
../src/stm32f4xx_it.c \
../src/stmeval_led.c \
../src/syscalls.c \
../src/sysinit.c \
../src/system_stm32f4xx.c \
../src/tlc5971.c 

OBJS += \
./src/adc.o \
./src/adc_dma.o \
./src/dma.o \
./src/exti.o \
./src/flash.o \
./src/gpio.o \
./src/main.o \
./src/max7301.o \
./src/nvic.o \
./src/rcc.o \
./src/spi.o \
./src/spi_dma.o \
./src/stm32f4xx_it.o \
./src/stmeval_led.o \
./src/syscalls.o \
./src/sysinit.o \
./src/system_stm32f4xx.o \
./src/tlc5971.o 

C_DEPS += \
./src/adc.d \
./src/adc_dma.d \
./src/dma.d \
./src/exti.d \
./src/flash.d \
./src/gpio.d \
./src/main.d \
./src/max7301.d \
./src/nvic.d \
./src/rcc.d \
./src/spi.d \
./src/spi_dma.d \
./src/stm32f4xx_it.d \
./src/stmeval_led.d \
./src/syscalls.d \
./src/sysinit.d \
./src/system_stm32f4xx.d \
./src/tlc5971.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -DSTM32F407xx -I"C:/Users/Daniel/workspace/keyboardLed/inc" -I"C:/Users/Daniel/workspace/keyboardLed/CMSIS/device" -I"C:/Users/Daniel/workspace/keyboardLed/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


