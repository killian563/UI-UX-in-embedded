################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/cs42l51/cs42l51.c \
../Drivers/Components/cs42l51/cs42l51_reg.c 

OBJS += \
./Drivers/Components/cs42l51/cs42l51.o \
./Drivers/Components/cs42l51/cs42l51_reg.o 

C_DEPS += \
./Drivers/Components/cs42l51/cs42l51.d \
./Drivers/Components/cs42l51/cs42l51_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/cs42l51/%.o Drivers/Components/cs42l51/%.su Drivers/Components/cs42l51/%.cyclo: ../Drivers/Components/cs42l51/%.c Drivers/Components/cs42l51/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/Drivers/STM32H7xx_HAL_Driver/Inc -I. -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/CM7/Drivers/BSP -I/home/yarboy/STM32CubeIDE/workspace_1.18.0/GSA1/CM7/Drivers/CMSIS/DSP/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-cs42l51

clean-Drivers-2f-Components-2f-cs42l51:
	-$(RM) ./Drivers/Components/cs42l51/cs42l51.cyclo ./Drivers/Components/cs42l51/cs42l51.d ./Drivers/Components/cs42l51/cs42l51.o ./Drivers/Components/cs42l51/cs42l51.su ./Drivers/Components/cs42l51/cs42l51_reg.cyclo ./Drivers/Components/cs42l51/cs42l51_reg.d ./Drivers/Components/cs42l51/cs42l51_reg.o ./Drivers/Components/cs42l51/cs42l51_reg.su

.PHONY: clean-Drivers-2f-Components-2f-cs42l51

