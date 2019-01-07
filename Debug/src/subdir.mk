################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/exti.c \
../src/flash.c \
../src/gpio.c \
../src/init_dev.c \
../src/main.c \
../src/nvic.c \
../src/rcc.c \
../src/spi.c \
../src/stm32f4xx_it.c \
../src/stmeval_led.c \
../src/syscalls.c \
../src/sysinit.c \
../src/system_stm32f4xx.c \
../src/tlc5971.c 

OBJS += \
./src/exti.o \
./src/flash.o \
./src/gpio.o \
./src/init_dev.o \
./src/main.o \
./src/nvic.o \
./src/rcc.o \
./src/spi.o \
./src/stm32f4xx_it.o \
./src/stmeval_led.o \
./src/syscalls.o \
./src/sysinit.o \
./src/system_stm32f4xx.o \
./src/tlc5971.o 

C_DEPS += \
./src/exti.d \
./src/flash.d \
./src/gpio.d \
./src/init_dev.d \
./src/main.d \
./src/nvic.d \
./src/rcc.d \
./src/spi.d \
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
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -DSTM32F407xx -I"/home/oem/workspace/LED_Keyboard/inc" -I"/home/oem/workspace/LED_Keyboard/CMSIS/device" -I"/home/oem/workspace/LED_Keyboard/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


