################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTOS/CortexMX_OS_Porting.c \
../RTOS/MYRTOS_FIFO.c \
../RTOS/Scheduler.c 

OBJS += \
./RTOS/CortexMX_OS_Porting.o \
./RTOS/MYRTOS_FIFO.o \
./RTOS/Scheduler.o 

C_DEPS += \
./RTOS/CortexMX_OS_Porting.d \
./RTOS/MYRTOS_FIFO.d \
./RTOS/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
RTOS/CortexMX_OS_Porting.o: ../RTOS/CortexMX_OS_Porting.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/RTOS" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/RTOS/inc" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/CMSIS_V5" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/EEPROM" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/KEYPAD" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/LCD" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/ADC" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/EXTI" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/GPIO" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/I2C" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/RCC" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/SPI" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/TIMERS" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/USART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"RTOS/CortexMX_OS_Porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
RTOS/MYRTOS_FIFO.o: ../RTOS/MYRTOS_FIFO.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/RTOS" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/RTOS/inc" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/CMSIS_V5" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/EEPROM" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/KEYPAD" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/LCD" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/ADC" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/EXTI" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/GPIO" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/I2C" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/RCC" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/SPI" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/TIMERS" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/USART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"RTOS/MYRTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
RTOS/Scheduler.o: ../RTOS/Scheduler.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/RTOS" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/RTOS/inc" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/CMSIS_V5" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/EEPROM" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/KEYPAD" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/ECU/LCD" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/ADC" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/EXTI" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/GPIO" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/I2C" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/RCC" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/SPI" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/TIMERS" -I"C:/Users/GTX/STM32CubeIDE/workspace_1.4.0/MY_RTOS/Drivers/MCAL/USART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"RTOS/Scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

