################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Example/User/CM7/engine/server/sv_client.c \
../Example/User/CM7/engine/server/sv_cmds.c \
../Example/User/CM7/engine/server/sv_custom.c \
../Example/User/CM7/engine/server/sv_filter.c \
../Example/User/CM7/engine/server/sv_frame.c \
../Example/User/CM7/engine/server/sv_game.c \
../Example/User/CM7/engine/server/sv_init.c \
../Example/User/CM7/engine/server/sv_log.c \
../Example/User/CM7/engine/server/sv_main.c \
../Example/User/CM7/engine/server/sv_move.c \
../Example/User/CM7/engine/server/sv_phys.c \
../Example/User/CM7/engine/server/sv_pmove.c \
../Example/User/CM7/engine/server/sv_save.c \
../Example/User/CM7/engine/server/sv_world.c 

C_DEPS += \
./Example/User/CM7/engine/server/sv_client.d \
./Example/User/CM7/engine/server/sv_cmds.d \
./Example/User/CM7/engine/server/sv_custom.d \
./Example/User/CM7/engine/server/sv_filter.d \
./Example/User/CM7/engine/server/sv_frame.d \
./Example/User/CM7/engine/server/sv_game.d \
./Example/User/CM7/engine/server/sv_init.d \
./Example/User/CM7/engine/server/sv_log.d \
./Example/User/CM7/engine/server/sv_main.d \
./Example/User/CM7/engine/server/sv_move.d \
./Example/User/CM7/engine/server/sv_phys.d \
./Example/User/CM7/engine/server/sv_pmove.d \
./Example/User/CM7/engine/server/sv_save.d \
./Example/User/CM7/engine/server/sv_world.d 

OBJS += \
./Example/User/CM7/engine/server/sv_client.o \
./Example/User/CM7/engine/server/sv_cmds.o \
./Example/User/CM7/engine/server/sv_custom.o \
./Example/User/CM7/engine/server/sv_filter.o \
./Example/User/CM7/engine/server/sv_frame.o \
./Example/User/CM7/engine/server/sv_game.o \
./Example/User/CM7/engine/server/sv_init.o \
./Example/User/CM7/engine/server/sv_log.o \
./Example/User/CM7/engine/server/sv_main.o \
./Example/User/CM7/engine/server/sv_move.o \
./Example/User/CM7/engine/server/sv_phys.o \
./Example/User/CM7/engine/server/sv_pmove.o \
./Example/User/CM7/engine/server/sv_save.o \
./Example/User/CM7/engine/server/sv_world.o 


# Each subdirectory must supply rules for building sources it contributes
Example/User/CM7/engine/server/%.o Example/User/CM7/engine/server/%.su Example/User/CM7/engine/server/%.cyclo: ../Example/User/CM7/engine/server/%.c Example/User/CM7/engine/server/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -DTS_MULTI_TOUCH_SUPPORTED -c -I../../../CM7/Inc -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Example/User/CM7" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/App" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/Target" -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32H747I-DISCO -I../../../Drivers/BSP/Components/Common -I../../../Utilities/lcd -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fms-extensions -I../Example/User/CM7/common/ -I../Example/User/CM7/engine/ -I../Example/User/CM7/engine/client/ -I../Example/User/CM7/engine/client/vgui/ -I../Example/User/CM7/engine/common/ -I../Example/User/CM7/engine/common/imagelib/ -I../Example/User/CM7/engine/filesystem/ -I../Example/User/CM7/engine/mainui/ -I../Example/User/CM7/engine/mainui/controls/ -I../Example/User/CM7/engine/mainui/font/ -I../Example/User/CM7/engine/mainui/menus/ -I../Example/User/CM7/engine/mainui/miniutl/ -I../Example/User/CM7/engine/mainui/model/ -I../Example/User/CM7/engine/opus/celt/ -I../Example/User/CM7/engine/opus/include/ -I../Example/User/CM7/engine/opus/silk/ -I../Example/User/CM7/engine/opus/silk/float/ -I../Example/User/CM7/engine/platform/ -I../Example/User/CM7/engine/ref/soft/ -I../Example/User/CM7/engine/sdk/cl_dll/ -I../Example/User/CM7/engine/sdk/dlls/ -I../Example/User/CM7/engine/sdk/pm_shared/ -I../Example/User/CM7/engine/server/ -I../Example/User/CM7/pm_shared/ -I../Example/User/CM7/public/ -D__GNU_VISIBLE=1 -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp  -D_snprintf=snprintf  -D_vsnprintf=vsnprintf  -D_LINUX  -DLINUX -DXASH_NO_LIBDL=1 -DXASH_NO_ASYNC_NS_RESOLVE=1 -DFLOAT_APPROX=1 -DOPUS_BUILD=1 -DXASH_GAMEDIR="valve" -DMAINUI_USE_CUSTOM_FONT_RENDER=1 -DSTDINT_H="<stdint.h>" -DHAVE_STDINT_H=1 -DPSAPI_VERSION=1 -DDBGHELP=1 -DALLOCA_H="<alloca.h>" -DXASH_REF_SOFT_ENABLED=1 -DCUSTOM_MODES=1 -DSINGLE_BINARY=1 -DHAVE_MALLOC_H=1 -DUSE_ALLOCA=1 -DPACKAGE_VERSION="1.3.1" -DXASH_LOW_MEMORY=2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Example-2f-User-2f-CM7-2f-engine-2f-server

clean-Example-2f-User-2f-CM7-2f-engine-2f-server:
	-$(RM) ./Example/User/CM7/engine/server/sv_client.cyclo ./Example/User/CM7/engine/server/sv_client.d ./Example/User/CM7/engine/server/sv_client.o ./Example/User/CM7/engine/server/sv_client.su ./Example/User/CM7/engine/server/sv_cmds.cyclo ./Example/User/CM7/engine/server/sv_cmds.d ./Example/User/CM7/engine/server/sv_cmds.o ./Example/User/CM7/engine/server/sv_cmds.su ./Example/User/CM7/engine/server/sv_custom.cyclo ./Example/User/CM7/engine/server/sv_custom.d ./Example/User/CM7/engine/server/sv_custom.o ./Example/User/CM7/engine/server/sv_custom.su ./Example/User/CM7/engine/server/sv_filter.cyclo ./Example/User/CM7/engine/server/sv_filter.d ./Example/User/CM7/engine/server/sv_filter.o ./Example/User/CM7/engine/server/sv_filter.su ./Example/User/CM7/engine/server/sv_frame.cyclo ./Example/User/CM7/engine/server/sv_frame.d ./Example/User/CM7/engine/server/sv_frame.o ./Example/User/CM7/engine/server/sv_frame.su ./Example/User/CM7/engine/server/sv_game.cyclo ./Example/User/CM7/engine/server/sv_game.d ./Example/User/CM7/engine/server/sv_game.o ./Example/User/CM7/engine/server/sv_game.su ./Example/User/CM7/engine/server/sv_init.cyclo ./Example/User/CM7/engine/server/sv_init.d ./Example/User/CM7/engine/server/sv_init.o ./Example/User/CM7/engine/server/sv_init.su ./Example/User/CM7/engine/server/sv_log.cyclo ./Example/User/CM7/engine/server/sv_log.d ./Example/User/CM7/engine/server/sv_log.o ./Example/User/CM7/engine/server/sv_log.su ./Example/User/CM7/engine/server/sv_main.cyclo ./Example/User/CM7/engine/server/sv_main.d ./Example/User/CM7/engine/server/sv_main.o ./Example/User/CM7/engine/server/sv_main.su ./Example/User/CM7/engine/server/sv_move.cyclo ./Example/User/CM7/engine/server/sv_move.d ./Example/User/CM7/engine/server/sv_move.o ./Example/User/CM7/engine/server/sv_move.su ./Example/User/CM7/engine/server/sv_phys.cyclo ./Example/User/CM7/engine/server/sv_phys.d ./Example/User/CM7/engine/server/sv_phys.o ./Example/User/CM7/engine/server/sv_phys.su ./Example/User/CM7/engine/server/sv_pmove.cyclo ./Example/User/CM7/engine/server/sv_pmove.d ./Example/User/CM7/engine/server/sv_pmove.o ./Example/User/CM7/engine/server/sv_pmove.su ./Example/User/CM7/engine/server/sv_save.cyclo ./Example/User/CM7/engine/server/sv_save.d ./Example/User/CM7/engine/server/sv_save.o ./Example/User/CM7/engine/server/sv_save.su ./Example/User/CM7/engine/server/sv_world.cyclo ./Example/User/CM7/engine/server/sv_world.d ./Example/User/CM7/engine/server/sv_world.o ./Example/User/CM7/engine/server/sv_world.su

.PHONY: clean-Example-2f-User-2f-CM7-2f-engine-2f-server

