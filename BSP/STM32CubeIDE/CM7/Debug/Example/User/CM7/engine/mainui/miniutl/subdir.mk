################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Example/User/CM7/engine/mainui/miniutl/bitstring.cpp \
../Example/User/CM7/engine/mainui/miniutl/generichash.cpp \
../Example/User/CM7/engine/mainui/miniutl/strtools.cpp \
../Example/User/CM7/engine/mainui/miniutl/utlbuffer.cpp \
../Example/User/CM7/engine/mainui/miniutl/utlmemory.cpp \
../Example/User/CM7/engine/mainui/miniutl/utlstring.cpp 

OBJS += \
./Example/User/CM7/engine/mainui/miniutl/bitstring.o \
./Example/User/CM7/engine/mainui/miniutl/generichash.o \
./Example/User/CM7/engine/mainui/miniutl/strtools.o \
./Example/User/CM7/engine/mainui/miniutl/utlbuffer.o \
./Example/User/CM7/engine/mainui/miniutl/utlmemory.o \
./Example/User/CM7/engine/mainui/miniutl/utlstring.o 

CPP_DEPS += \
./Example/User/CM7/engine/mainui/miniutl/bitstring.d \
./Example/User/CM7/engine/mainui/miniutl/generichash.d \
./Example/User/CM7/engine/mainui/miniutl/strtools.d \
./Example/User/CM7/engine/mainui/miniutl/utlbuffer.d \
./Example/User/CM7/engine/mainui/miniutl/utlmemory.d \
./Example/User/CM7/engine/mainui/miniutl/utlstring.d 


# Each subdirectory must supply rules for building sources it contributes
Example/User/CM7/engine/mainui/miniutl/%.o Example/User/CM7/engine/mainui/miniutl/%.su Example/User/CM7/engine/mainui/miniutl/%.cyclo: ../Example/User/CM7/engine/mainui/miniutl/%.cpp Example/User/CM7/engine/mainui/miniutl/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_STM32H747I_DISCO -DDEBUG -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -DTS_MULTI_TOUCH_SUPPORTED -c -I../../../CM7/Inc -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Example/User/CM7" -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32H747I-DISCO -I../../../Drivers/BSP/Components/Common -I../../../Utilities/lcd -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp  -D_snprintf=snprintf  -D__GNU_VISIBLE=1  -D_vsnprintf=vsnprintf  -D_LINUX  -DLINUX -DXASH_NO_LIBDL=1 -DXASH_NO_ASYNC_NS_RESOLVE=1 -DFLOAT_APPROX=1 -DOPUS_BUILD=1 -DXASH_GAMEDIR="valve" -DMAINUI_USE_CUSTOM_FONT_RENDER=1 -DSTDINT_H="<stdint.h>" -DHAVE_STDINT_H=1 -DPSAPI_VERSION=1 -DDBGHELP=1 -DALLOCA_H="<alloca.h>" -DXASH_REF_SOFT_ENABLED=1 -DCUSTOM_MODES=1 -DSINGLE_BINARY=1 -DHAVE_MALLOC_H=1 -DUSE_ALLOCA=1 -DPACKAGE_VERSION="1.3.1" -DXASH_LOW_MEMORY=2 -ffast-math -I../Example/User/CM7/common/ -I../Example/User/CM7/engine/ -I../Example/User/CM7/engine/client/ -I../Example/User/CM7/engine/client/vgui/ -I../Example/User/CM7/engine/common/ -I../Example/User/CM7/engine/common/imagelib/ -I../Example/User/CM7/engine/filesystem/ -I../Example/User/CM7/engine/mainui/ -I../Example/User/CM7/engine/mainui/controls/ -I../Example/User/CM7/engine/mainui/font/ -I../Example/User/CM7/engine/mainui/menus/ -I../Example/User/CM7/engine/mainui/miniutl/ -I../Example/User/CM7/engine/mainui/model/ -I../Example/User/CM7/engine/opus/celt/ -I../Example/User/CM7/engine/opus/include/ -I../Example/User/CM7/engine/opus/silk/ -I../Example/User/CM7/engine/opus/silk/float/ -I../Example/User/CM7/engine/platform/ -I../Example/User/CM7/engine/ref/soft/ -I../Example/User/CM7/engine/sdk/cl_dll/ -I../Example/User/CM7/engine/sdk/dlls/ -I../Example/User/CM7/engine/sdk/pm_shared/ -I../Example/User/CM7/engine/server/ -I../Example/User/CM7/pm_shared/ -I../Example/User/CM7/public/ -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Example-2f-User-2f-CM7-2f-engine-2f-mainui-2f-miniutl

clean-Example-2f-User-2f-CM7-2f-engine-2f-mainui-2f-miniutl:
	-$(RM) ./Example/User/CM7/engine/mainui/miniutl/bitstring.cyclo ./Example/User/CM7/engine/mainui/miniutl/bitstring.d ./Example/User/CM7/engine/mainui/miniutl/bitstring.o ./Example/User/CM7/engine/mainui/miniutl/bitstring.su ./Example/User/CM7/engine/mainui/miniutl/generichash.cyclo ./Example/User/CM7/engine/mainui/miniutl/generichash.d ./Example/User/CM7/engine/mainui/miniutl/generichash.o ./Example/User/CM7/engine/mainui/miniutl/generichash.su ./Example/User/CM7/engine/mainui/miniutl/strtools.cyclo ./Example/User/CM7/engine/mainui/miniutl/strtools.d ./Example/User/CM7/engine/mainui/miniutl/strtools.o ./Example/User/CM7/engine/mainui/miniutl/strtools.su ./Example/User/CM7/engine/mainui/miniutl/utlbuffer.cyclo ./Example/User/CM7/engine/mainui/miniutl/utlbuffer.d ./Example/User/CM7/engine/mainui/miniutl/utlbuffer.o ./Example/User/CM7/engine/mainui/miniutl/utlbuffer.su ./Example/User/CM7/engine/mainui/miniutl/utlmemory.cyclo ./Example/User/CM7/engine/mainui/miniutl/utlmemory.d ./Example/User/CM7/engine/mainui/miniutl/utlmemory.o ./Example/User/CM7/engine/mainui/miniutl/utlmemory.su ./Example/User/CM7/engine/mainui/miniutl/utlstring.cyclo ./Example/User/CM7/engine/mainui/miniutl/utlstring.d ./Example/User/CM7/engine/mainui/miniutl/utlstring.o ./Example/User/CM7/engine/mainui/miniutl/utlstring.su

.PHONY: clean-Example-2f-User-2f-CM7-2f-engine-2f-mainui-2f-miniutl

