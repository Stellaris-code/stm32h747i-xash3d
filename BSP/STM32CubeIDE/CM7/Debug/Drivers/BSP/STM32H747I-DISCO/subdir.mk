################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.c \
../Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_audio.c \
../Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.c \
../Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_camera.c \
../Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.c \
../Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_qspi.c \
../Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sd.c \
../Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.c \
../Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.c 

C_DEPS += \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.d \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_audio.d \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.d \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_camera.d \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.d \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_qspi.d \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sd.d \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.d \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.d 

OBJS += \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.o \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_audio.o \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.o \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_camera.o \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.o \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_qspi.o \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sd.o \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.o \
./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H747I-DISCO/%.o Drivers/BSP/STM32H747I-DISCO/%.su Drivers/BSP/STM32H747I-DISCO/%.cyclo: ../Drivers/BSP/STM32H747I-DISCO/%.c Drivers/BSP/STM32H747I-DISCO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -DTS_MULTI_TOUCH_SUPPORTED -c -I../../../CM7/Inc -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Example/User/CM7" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/App" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/Target" -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32H747I-DISCO -I../../../Drivers/BSP/Components/Common -I../../../Utilities/lcd -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fms-extensions -I../Example/User/CM7/common/ -I../Example/User/CM7/engine/ -I../Example/User/CM7/engine/client/ -I../Example/User/CM7/engine/client/vgui/ -I../Example/User/CM7/engine/common/ -I../Example/User/CM7/engine/common/imagelib/ -I../Example/User/CM7/engine/filesystem/ -I../Example/User/CM7/engine/mainui/ -I../Example/User/CM7/engine/mainui/controls/ -I../Example/User/CM7/engine/mainui/font/ -I../Example/User/CM7/engine/mainui/menus/ -I../Example/User/CM7/engine/mainui/miniutl/ -I../Example/User/CM7/engine/mainui/model/ -I../Example/User/CM7/engine/opus/celt/ -I../Example/User/CM7/engine/opus/include/ -I../Example/User/CM7/engine/opus/silk/ -I../Example/User/CM7/engine/opus/silk/float/ -I../Example/User/CM7/engine/platform/ -I../Example/User/CM7/engine/ref/soft/ -I../Example/User/CM7/engine/sdk/cl_dll/ -I../Example/User/CM7/engine/sdk/dlls/ -I../Example/User/CM7/engine/sdk/pm_shared/ -I../Example/User/CM7/engine/server/ -I../Example/User/CM7/pm_shared/ -I../Example/User/CM7/public/ -D__GNU_VISIBLE=1 -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp  -D_snprintf=snprintf  -D_vsnprintf=vsnprintf  -D_LINUX  -DLINUX -DXASH_NO_LIBDL=1 -DXASH_NO_ASYNC_NS_RESOLVE=1 -DFLOAT_APPROX=1 -DOPUS_BUILD=1 -DXASH_GAMEDIR="valve" -DMAINUI_USE_CUSTOM_FONT_RENDER=1 -DSTDINT_H="<stdint.h>" -DHAVE_STDINT_H=1 -DPSAPI_VERSION=1 -DDBGHELP=1 -DALLOCA_H="<alloca.h>" -DXASH_REF_SOFT_ENABLED=1 -DCUSTOM_MODES=1 -DSINGLE_BINARY=1 -DHAVE_MALLOC_H=1 -DUSE_ALLOCA=1 -DPACKAGE_VERSION="1.3.1" -DXASH_LOW_MEMORY=2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32H747I-2d-DISCO

clean-Drivers-2f-BSP-2f-STM32H747I-2d-DISCO:
	-$(RM) ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.cyclo ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.d ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.o ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.su ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_audio.cyclo ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_audio.d ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_audio.o ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_audio.su ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.cyclo ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.d ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.o ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.su ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_camera.cyclo ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_camera.d ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_camera.o ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_camera.su ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.cyclo ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.d ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.o ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.su ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_qspi.cyclo ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_qspi.d ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_qspi.o ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_qspi.su ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sd.cyclo ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sd.d ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sd.o ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sd.su ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.cyclo ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.d ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.o ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.su ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.cyclo ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.d ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.o ./Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32H747I-2d-DISCO

