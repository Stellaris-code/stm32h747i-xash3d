################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Example/User/CM7/engine/opus/celt/bands.c \
../Example/User/CM7/engine/opus/celt/celt.c \
../Example/User/CM7/engine/opus/celt/celt_decoder.c \
../Example/User/CM7/engine/opus/celt/celt_encoder.c \
../Example/User/CM7/engine/opus/celt/celt_lpc.c \
../Example/User/CM7/engine/opus/celt/cwrs.c \
../Example/User/CM7/engine/opus/celt/entcode.c \
../Example/User/CM7/engine/opus/celt/entdec.c \
../Example/User/CM7/engine/opus/celt/entenc.c \
../Example/User/CM7/engine/opus/celt/kiss_fft.c \
../Example/User/CM7/engine/opus/celt/laplace.c \
../Example/User/CM7/engine/opus/celt/mathops.c \
../Example/User/CM7/engine/opus/celt/mdct.c \
../Example/User/CM7/engine/opus/celt/modes.c \
../Example/User/CM7/engine/opus/celt/pitch.c \
../Example/User/CM7/engine/opus/celt/quant_bands.c \
../Example/User/CM7/engine/opus/celt/rate.c \
../Example/User/CM7/engine/opus/celt/vq.c 

C_DEPS += \
./Example/User/CM7/engine/opus/celt/bands.d \
./Example/User/CM7/engine/opus/celt/celt.d \
./Example/User/CM7/engine/opus/celt/celt_decoder.d \
./Example/User/CM7/engine/opus/celt/celt_encoder.d \
./Example/User/CM7/engine/opus/celt/celt_lpc.d \
./Example/User/CM7/engine/opus/celt/cwrs.d \
./Example/User/CM7/engine/opus/celt/entcode.d \
./Example/User/CM7/engine/opus/celt/entdec.d \
./Example/User/CM7/engine/opus/celt/entenc.d \
./Example/User/CM7/engine/opus/celt/kiss_fft.d \
./Example/User/CM7/engine/opus/celt/laplace.d \
./Example/User/CM7/engine/opus/celt/mathops.d \
./Example/User/CM7/engine/opus/celt/mdct.d \
./Example/User/CM7/engine/opus/celt/modes.d \
./Example/User/CM7/engine/opus/celt/pitch.d \
./Example/User/CM7/engine/opus/celt/quant_bands.d \
./Example/User/CM7/engine/opus/celt/rate.d \
./Example/User/CM7/engine/opus/celt/vq.d 

OBJS += \
./Example/User/CM7/engine/opus/celt/bands.o \
./Example/User/CM7/engine/opus/celt/celt.o \
./Example/User/CM7/engine/opus/celt/celt_decoder.o \
./Example/User/CM7/engine/opus/celt/celt_encoder.o \
./Example/User/CM7/engine/opus/celt/celt_lpc.o \
./Example/User/CM7/engine/opus/celt/cwrs.o \
./Example/User/CM7/engine/opus/celt/entcode.o \
./Example/User/CM7/engine/opus/celt/entdec.o \
./Example/User/CM7/engine/opus/celt/entenc.o \
./Example/User/CM7/engine/opus/celt/kiss_fft.o \
./Example/User/CM7/engine/opus/celt/laplace.o \
./Example/User/CM7/engine/opus/celt/mathops.o \
./Example/User/CM7/engine/opus/celt/mdct.o \
./Example/User/CM7/engine/opus/celt/modes.o \
./Example/User/CM7/engine/opus/celt/pitch.o \
./Example/User/CM7/engine/opus/celt/quant_bands.o \
./Example/User/CM7/engine/opus/celt/rate.o \
./Example/User/CM7/engine/opus/celt/vq.o 


# Each subdirectory must supply rules for building sources it contributes
Example/User/CM7/engine/opus/celt/%.o Example/User/CM7/engine/opus/celt/%.su Example/User/CM7/engine/opus/celt/%.cyclo: ../Example/User/CM7/engine/opus/celt/%.c Example/User/CM7/engine/opus/celt/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -DTS_MULTI_TOUCH_SUPPORTED -c -I../../../CM7/Inc -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Example/User/CM7" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/App" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/Target" -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32H747I-DISCO -I../../../Drivers/BSP/Components/Common -I../../../Utilities/lcd -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fms-extensions -I../Example/User/CM7/common/ -I../Example/User/CM7/engine/ -I../Example/User/CM7/engine/client/ -I../Example/User/CM7/engine/client/vgui/ -I../Example/User/CM7/engine/common/ -I../Example/User/CM7/engine/common/imagelib/ -I../Example/User/CM7/engine/filesystem/ -I../Example/User/CM7/engine/mainui/ -I../Example/User/CM7/engine/mainui/controls/ -I../Example/User/CM7/engine/mainui/font/ -I../Example/User/CM7/engine/mainui/menus/ -I../Example/User/CM7/engine/mainui/miniutl/ -I../Example/User/CM7/engine/mainui/model/ -I../Example/User/CM7/engine/opus/celt/ -I../Example/User/CM7/engine/opus/include/ -I../Example/User/CM7/engine/opus/silk/ -I../Example/User/CM7/engine/opus/silk/float/ -I../Example/User/CM7/engine/platform/ -I../Example/User/CM7/engine/ref/soft/ -I../Example/User/CM7/engine/sdk/cl_dll/ -I../Example/User/CM7/engine/sdk/dlls/ -I../Example/User/CM7/engine/sdk/pm_shared/ -I../Example/User/CM7/engine/server/ -I../Example/User/CM7/pm_shared/ -I../Example/User/CM7/public/ -D__GNU_VISIBLE=1 -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp  -D_snprintf=snprintf  -D_vsnprintf=vsnprintf  -D_LINUX  -DLINUX -DXASH_NO_LIBDL=1 -DXASH_NO_ASYNC_NS_RESOLVE=1 -DFLOAT_APPROX=1 -DOPUS_BUILD=1 -DXASH_GAMEDIR="valve" -DMAINUI_USE_CUSTOM_FONT_RENDER=1 -DSTDINT_H="<stdint.h>" -DHAVE_STDINT_H=1 -DPSAPI_VERSION=1 -DDBGHELP=1 -DALLOCA_H="<alloca.h>" -DXASH_REF_SOFT_ENABLED=1 -DCUSTOM_MODES=1 -DSINGLE_BINARY=1 -DHAVE_MALLOC_H=1 -DUSE_ALLOCA=1 -DPACKAGE_VERSION="1.3.1" -DXASH_LOW_MEMORY=2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Example-2f-User-2f-CM7-2f-engine-2f-opus-2f-celt

clean-Example-2f-User-2f-CM7-2f-engine-2f-opus-2f-celt:
	-$(RM) ./Example/User/CM7/engine/opus/celt/bands.cyclo ./Example/User/CM7/engine/opus/celt/bands.d ./Example/User/CM7/engine/opus/celt/bands.o ./Example/User/CM7/engine/opus/celt/bands.su ./Example/User/CM7/engine/opus/celt/celt.cyclo ./Example/User/CM7/engine/opus/celt/celt.d ./Example/User/CM7/engine/opus/celt/celt.o ./Example/User/CM7/engine/opus/celt/celt.su ./Example/User/CM7/engine/opus/celt/celt_decoder.cyclo ./Example/User/CM7/engine/opus/celt/celt_decoder.d ./Example/User/CM7/engine/opus/celt/celt_decoder.o ./Example/User/CM7/engine/opus/celt/celt_decoder.su ./Example/User/CM7/engine/opus/celt/celt_encoder.cyclo ./Example/User/CM7/engine/opus/celt/celt_encoder.d ./Example/User/CM7/engine/opus/celt/celt_encoder.o ./Example/User/CM7/engine/opus/celt/celt_encoder.su ./Example/User/CM7/engine/opus/celt/celt_lpc.cyclo ./Example/User/CM7/engine/opus/celt/celt_lpc.d ./Example/User/CM7/engine/opus/celt/celt_lpc.o ./Example/User/CM7/engine/opus/celt/celt_lpc.su ./Example/User/CM7/engine/opus/celt/cwrs.cyclo ./Example/User/CM7/engine/opus/celt/cwrs.d ./Example/User/CM7/engine/opus/celt/cwrs.o ./Example/User/CM7/engine/opus/celt/cwrs.su ./Example/User/CM7/engine/opus/celt/entcode.cyclo ./Example/User/CM7/engine/opus/celt/entcode.d ./Example/User/CM7/engine/opus/celt/entcode.o ./Example/User/CM7/engine/opus/celt/entcode.su ./Example/User/CM7/engine/opus/celt/entdec.cyclo ./Example/User/CM7/engine/opus/celt/entdec.d ./Example/User/CM7/engine/opus/celt/entdec.o ./Example/User/CM7/engine/opus/celt/entdec.su ./Example/User/CM7/engine/opus/celt/entenc.cyclo ./Example/User/CM7/engine/opus/celt/entenc.d ./Example/User/CM7/engine/opus/celt/entenc.o ./Example/User/CM7/engine/opus/celt/entenc.su ./Example/User/CM7/engine/opus/celt/kiss_fft.cyclo ./Example/User/CM7/engine/opus/celt/kiss_fft.d ./Example/User/CM7/engine/opus/celt/kiss_fft.o ./Example/User/CM7/engine/opus/celt/kiss_fft.su ./Example/User/CM7/engine/opus/celt/laplace.cyclo ./Example/User/CM7/engine/opus/celt/laplace.d ./Example/User/CM7/engine/opus/celt/laplace.o ./Example/User/CM7/engine/opus/celt/laplace.su ./Example/User/CM7/engine/opus/celt/mathops.cyclo ./Example/User/CM7/engine/opus/celt/mathops.d ./Example/User/CM7/engine/opus/celt/mathops.o ./Example/User/CM7/engine/opus/celt/mathops.su ./Example/User/CM7/engine/opus/celt/mdct.cyclo ./Example/User/CM7/engine/opus/celt/mdct.d ./Example/User/CM7/engine/opus/celt/mdct.o ./Example/User/CM7/engine/opus/celt/mdct.su ./Example/User/CM7/engine/opus/celt/modes.cyclo ./Example/User/CM7/engine/opus/celt/modes.d ./Example/User/CM7/engine/opus/celt/modes.o ./Example/User/CM7/engine/opus/celt/modes.su ./Example/User/CM7/engine/opus/celt/pitch.cyclo ./Example/User/CM7/engine/opus/celt/pitch.d ./Example/User/CM7/engine/opus/celt/pitch.o ./Example/User/CM7/engine/opus/celt/pitch.su ./Example/User/CM7/engine/opus/celt/quant_bands.cyclo ./Example/User/CM7/engine/opus/celt/quant_bands.d ./Example/User/CM7/engine/opus/celt/quant_bands.o ./Example/User/CM7/engine/opus/celt/quant_bands.su ./Example/User/CM7/engine/opus/celt/rate.cyclo ./Example/User/CM7/engine/opus/celt/rate.d ./Example/User/CM7/engine/opus/celt/rate.o ./Example/User/CM7/engine/opus/celt/rate.su ./Example/User/CM7/engine/opus/celt/vq.cyclo ./Example/User/CM7/engine/opus/celt/vq.d ./Example/User/CM7/engine/opus/celt/vq.o ./Example/User/CM7/engine/opus/celt/vq.su

.PHONY: clean-Example-2f-User-2f-CM7-2f-engine-2f-opus-2f-celt

