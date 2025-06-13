################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/ov5640/ov5640.c \
../Drivers/Components/ov5640/ov5640_reg.c 

OBJS += \
./Drivers/Components/ov5640/ov5640.o \
./Drivers/Components/ov5640/ov5640_reg.o 

C_DEPS += \
./Drivers/Components/ov5640/ov5640.d \
./Drivers/Components/ov5640/ov5640_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/ov5640/%.o Drivers/Components/ov5640/%.su Drivers/Components/ov5640/%.cyclo: ../Drivers/Components/ov5640/%.c Drivers/Components/ov5640/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/Drivers/STM32H7xx_HAL_Driver/Inc -I. -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/CM7/Drivers/BSP -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/CM7/Drivers/CMSIS/DSP/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-ov5640

clean-Drivers-2f-Components-2f-ov5640:
	-$(RM) ./Drivers/Components/ov5640/ov5640.cyclo ./Drivers/Components/ov5640/ov5640.d ./Drivers/Components/ov5640/ov5640.o ./Drivers/Components/ov5640/ov5640.su ./Drivers/Components/ov5640/ov5640_reg.cyclo ./Drivers/Components/ov5640/ov5640_reg.d ./Drivers/Components/ov5640/ov5640_reg.o ./Drivers/Components/ov5640/ov5640_reg.su

.PHONY: clean-Drivers-2f-Components-2f-ov5640

