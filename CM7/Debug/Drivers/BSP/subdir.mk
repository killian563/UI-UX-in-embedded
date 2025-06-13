################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/stm32h745i_discovery.c \
../Drivers/BSP/stm32h745i_discovery_audio.c \
../Drivers/BSP/stm32h745i_discovery_bus.c \
../Drivers/BSP/stm32h745i_discovery_lcd.c \
../Drivers/BSP/stm32h745i_discovery_qspi.c \
../Drivers/BSP/stm32h745i_discovery_sdram.c \
../Drivers/BSP/stm32h745i_discovery_ts.c 

OBJS += \
./Drivers/BSP/stm32h745i_discovery.o \
./Drivers/BSP/stm32h745i_discovery_audio.o \
./Drivers/BSP/stm32h745i_discovery_bus.o \
./Drivers/BSP/stm32h745i_discovery_lcd.o \
./Drivers/BSP/stm32h745i_discovery_qspi.o \
./Drivers/BSP/stm32h745i_discovery_sdram.o \
./Drivers/BSP/stm32h745i_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/stm32h745i_discovery.d \
./Drivers/BSP/stm32h745i_discovery_audio.d \
./Drivers/BSP/stm32h745i_discovery_bus.d \
./Drivers/BSP/stm32h745i_discovery_lcd.d \
./Drivers/BSP/stm32h745i_discovery_qspi.d \
./Drivers/BSP/stm32h745i_discovery_sdram.d \
./Drivers/BSP/stm32h745i_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/%.o Drivers/BSP/%.su Drivers/BSP/%.cyclo: ../Drivers/BSP/%.c Drivers/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/Drivers/STM32H7xx_HAL_Driver/Inc -I. -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/CM7/Drivers/BSP -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/CM7/Drivers/CMSIS/DSP/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP

clean-Drivers-2f-BSP:
	-$(RM) ./Drivers/BSP/stm32h745i_discovery.cyclo ./Drivers/BSP/stm32h745i_discovery.d ./Drivers/BSP/stm32h745i_discovery.o ./Drivers/BSP/stm32h745i_discovery.su ./Drivers/BSP/stm32h745i_discovery_audio.cyclo ./Drivers/BSP/stm32h745i_discovery_audio.d ./Drivers/BSP/stm32h745i_discovery_audio.o ./Drivers/BSP/stm32h745i_discovery_audio.su ./Drivers/BSP/stm32h745i_discovery_bus.cyclo ./Drivers/BSP/stm32h745i_discovery_bus.d ./Drivers/BSP/stm32h745i_discovery_bus.o ./Drivers/BSP/stm32h745i_discovery_bus.su ./Drivers/BSP/stm32h745i_discovery_lcd.cyclo ./Drivers/BSP/stm32h745i_discovery_lcd.d ./Drivers/BSP/stm32h745i_discovery_lcd.o ./Drivers/BSP/stm32h745i_discovery_lcd.su ./Drivers/BSP/stm32h745i_discovery_qspi.cyclo ./Drivers/BSP/stm32h745i_discovery_qspi.d ./Drivers/BSP/stm32h745i_discovery_qspi.o ./Drivers/BSP/stm32h745i_discovery_qspi.su ./Drivers/BSP/stm32h745i_discovery_sdram.cyclo ./Drivers/BSP/stm32h745i_discovery_sdram.d ./Drivers/BSP/stm32h745i_discovery_sdram.o ./Drivers/BSP/stm32h745i_discovery_sdram.su ./Drivers/BSP/stm32h745i_discovery_ts.cyclo ./Drivers/BSP/stm32h745i_discovery_ts.d ./Drivers/BSP/stm32h745i_discovery_ts.o ./Drivers/BSP/stm32h745i_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP

