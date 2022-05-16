################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MCAL/ADC_program.c \
../src/MCAL/DIO_program.c \
../src/MCAL/RCC_program.c \
../src/MCAL/STK_program.c \
../src/MCAL/USART_program.c 

OBJS += \
./src/MCAL/ADC_program.o \
./src/MCAL/DIO_program.o \
./src/MCAL/RCC_program.o \
./src/MCAL/STK_program.o \
./src/MCAL/USART_program.o 

C_DEPS += \
./src/MCAL/ADC_program.d \
./src/MCAL/DIO_program.d \
./src/MCAL/RCC_program.d \
./src/MCAL/STK_program.d \
./src/MCAL/USART_program.d 


# Each subdirectory must supply rules for building sources it contributes
src/MCAL/%.o: ../src/MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"E:\EMBEDDED SYSTEM\STM\dirFolder\IntergrationAndApplication\include\HAL" -I"E:\EMBEDDED SYSTEM\STM\dirFolder\IntergrationAndApplication\include\MCAL" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


