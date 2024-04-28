################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f103c8tx.s 

OBJS += \
./Startup/startup_stm32f103c8tx.o 

S_DEPS += \
./Startup/startup_stm32f103c8tx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_stm32f103c8tx.o: ../Startup/startup_stm32f103c8tx.s
	arm-none-eabi-gcc  -gdwarf-2 -mcpu=cortex-m3 -g3 -c -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/EEPROM" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/KEYPAD" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/LCD" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/ADC" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/EXTI" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/GPIO" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/I2C" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/RCC" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/SPI" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/TIMERS" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/USART" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/RTOS" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/RTOS/inc" -x assembler-with-cpp -MMD -MP -MF"Startup/startup_stm32f103c8tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

