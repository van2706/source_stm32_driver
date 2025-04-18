################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Src/gpio_f103.c \
../Driver/Src/systick_f103.c \
../Driver/Src/usart_f103.c 

OBJS += \
./Driver/Src/gpio_f103.o \
./Driver/Src/systick_f103.o \
./Driver/Src/usart_f103.o 

C_DEPS += \
./Driver/Src/gpio_f103.d \
./Driver/Src/systick_f103.d \
./Driver/Src/usart_f103.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/%.o Driver/Src/%.su Driver/Src/%.cyclo: ../Driver/Src/%.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/DINHVAN/STM32F407/STM32/driver_f103/Driver/Inc" -I"D:/DINHVAN/STM32F407/STM32/driver_f103/Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-Src

clean-Driver-2f-Src:
	-$(RM) ./Driver/Src/gpio_f103.cyclo ./Driver/Src/gpio_f103.d ./Driver/Src/gpio_f103.o ./Driver/Src/gpio_f103.su ./Driver/Src/systick_f103.cyclo ./Driver/Src/systick_f103.d ./Driver/Src/systick_f103.o ./Driver/Src/systick_f103.su ./Driver/Src/usart_f103.cyclo ./Driver/Src/usart_f103.d ./Driver/Src/usart_f103.o ./Driver/Src/usart_f103.su

.PHONY: clean-Driver-2f-Src

