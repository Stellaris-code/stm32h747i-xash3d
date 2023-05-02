################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp.c \
../Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_if_template.c \
../Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_opt.c \
../Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_storage.c 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp.d \
./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_if_template.d \
./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_opt.d \
./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_storage.d 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp.o \
./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_if_template.o \
./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_opt.o \
./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_storage.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/%.o Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/%.su Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/%.cyclo: ../Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/%.c Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -DTS_MULTI_TOUCH_SUPPORTED -c -I../../../CM7/Inc -I"C:/Users/Ya2nb/STM32CubeIDE/workspace_1.12.0/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/Ya2nb/STM32CubeIDE/workspace_1.12.0/BSP/STM32CubeIDE/CM7/Example/User/CM7" -I"C:/Users/Ya2nb/STM32CubeIDE/workspace_1.12.0/BSP/STM32CubeIDE/CM7/USB_DEVICE" -I"C:/Users/Ya2nb/STM32CubeIDE/workspace_1.12.0/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Ya2nb/STM32CubeIDE/workspace_1.12.0/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Ya2nb/STM32CubeIDE/workspace_1.12.0/BSP/STM32CubeIDE/CM7/USB_DEVICE/Target" -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32H747I-DISCO -I../../../Drivers/BSP/Components/Common -I../../../Utilities/lcd -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fms-extensions -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Class-2f-MTP-2f-Src

clean-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Class-2f-MTP-2f-Src:
	-$(RM) ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp.cyclo ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp.d ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp.o ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp.su ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_if_template.cyclo ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_if_template.d ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_if_template.o ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_if_template.su ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_opt.cyclo ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_opt.d ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_opt.o ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_opt.su ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_storage.cyclo ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_storage.d ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_storage.o ./Middlewares/ST/STM32_USB_Device_Library/Class/MTP/Src/usbd_mtp_storage.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Class-2f-MTP-2f-Src

