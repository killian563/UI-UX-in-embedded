################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/stmpe811/stmpe811.c \
../Drivers/Components/stmpe811/stmpe811_reg.c 

OBJS += \
./Drivers/Components/stmpe811/stmpe811.o \
./Drivers/Components/stmpe811/stmpe811_reg.o 

C_DEPS += \
./Drivers/Components/stmpe811/stmpe811.d \
./Drivers/Components/stmpe811/stmpe811_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/stmpe811/%.o Drivers/Components/stmpe811/%.su Drivers/Components/stmpe811/%.cyclo: ../Drivers/Components/stmpe811/%.c Drivers/Components/stmpe811/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/Drivers/STM32H7xx_HAL_Driver/Inc -I. -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/CM7/Drivers/BSP -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/CM7/Drivers/CMSIS/DSP/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-stmpe811

clean-Drivers-2f-Components-2f-stmpe811:
	-$(RM) ./Drivers/Components/stmpe811/stmpe811.cyclo ./Drivers/Components/stmpe811/stmpe811.d ./Drivers/Components/stmpe811/stmpe811.o ./Drivers/Components/stmpe811/stmpe811.su ./Drivers/Components/stmpe811/stmpe811_reg.cyclo ./Drivers/Components/stmpe811/stmpe811_reg.d ./Drivers/Components/stmpe811/stmpe811_reg.o ./Drivers/Components/stmpe811/stmpe811_reg.su

.PHONY: clean-Drivers-2f-Components-2f-stmpe811

