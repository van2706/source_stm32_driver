################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Src/gpio_f407.c \
../Driver/Src/rcc_f407.c \
../Driver/Src/spi_f407.c \
../Driver/Src/usart_f407.c 

OBJS += \
./Driver/Src/gpio_f407.o \
./Driver/Src/rcc_f407.o \
./Driver/Src/spi_f407.o \
./Driver/Src/usart_f407.o 

C_DEPS += \
./Driver/Src/gpio_f407.d \
./Driver/Src/rcc_f407.d \
./Driver/Src/spi_f407.d \
./Driver/Src/usart_f407.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/%.o Driver/Src/%.su Driver/Src/%.cyclo: ../Driver/Src/%.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/DINHVAN/STM32F407/STM32/STM32F4_DRIVER/Driver" -I"D:/DINHVAN/STM32F407/STM32/STM32F4_DRIVER/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Src

clean-Driver-2f-Src:
	-$(RM) ./Driver/Src/gpio_f407.cyclo ./Driver/Src/gpio_f407.d ./Driver/Src/gpio_f407.o ./Driver/Src/gpio_f407.su ./Driver/Src/rcc_f407.cyclo ./Driver/Src/rcc_f407.d ./Driver/Src/rcc_f407.o ./Driver/Src/rcc_f407.su ./Driver/Src/spi_f407.cyclo ./Driver/Src/spi_f407.d ./Driver/Src/spi_f407.o ./Driver/Src/spi_f407.su ./Driver/Src/usart_f407.cyclo ./Driver/Src/usart_f407.d ./Driver/Src/usart_f407.o ./Driver/Src/usart_f407.su

.PHONY: clean-Driver-2f-Src

