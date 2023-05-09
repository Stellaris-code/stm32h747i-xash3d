################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Example/User/CM7/engine/ref/soft/r_aclip.c \
../Example/User/CM7/engine/ref/soft/r_beams.c \
../Example/User/CM7/engine/ref/soft/r_bsp.c \
../Example/User/CM7/engine/ref/soft/r_context.c \
../Example/User/CM7/engine/ref/soft/r_decals.c \
../Example/User/CM7/engine/ref/soft/r_draw.c \
../Example/User/CM7/engine/ref/soft/r_edge.c \
../Example/User/CM7/engine/ref/soft/r_glblit.c \
../Example/User/CM7/engine/ref/soft/r_image.c \
../Example/User/CM7/engine/ref/soft/r_light.c \
../Example/User/CM7/engine/ref/soft/r_main.c \
../Example/User/CM7/engine/ref/soft/r_math.c \
../Example/User/CM7/engine/ref/soft/r_misc.c \
../Example/User/CM7/engine/ref/soft/r_part.c \
../Example/User/CM7/engine/ref/soft/r_polyse.c \
../Example/User/CM7/engine/ref/soft/r_rast.c \
../Example/User/CM7/engine/ref/soft/r_scan.c \
../Example/User/CM7/engine/ref/soft/r_sprite.c \
../Example/User/CM7/engine/ref/soft/r_studio.c \
../Example/User/CM7/engine/ref/soft/r_surf.c \
../Example/User/CM7/engine/ref/soft/r_trialias.c \
../Example/User/CM7/engine/ref/soft/r_triapi.c \
../Example/User/CM7/engine/ref/soft/r_vgui.c 

C_DEPS += \
./Example/User/CM7/engine/ref/soft/r_aclip.d \
./Example/User/CM7/engine/ref/soft/r_beams.d \
./Example/User/CM7/engine/ref/soft/r_bsp.d \
./Example/User/CM7/engine/ref/soft/r_context.d \
./Example/User/CM7/engine/ref/soft/r_decals.d \
./Example/User/CM7/engine/ref/soft/r_draw.d \
./Example/User/CM7/engine/ref/soft/r_edge.d \
./Example/User/CM7/engine/ref/soft/r_glblit.d \
./Example/User/CM7/engine/ref/soft/r_image.d \
./Example/User/CM7/engine/ref/soft/r_light.d \
./Example/User/CM7/engine/ref/soft/r_main.d \
./Example/User/CM7/engine/ref/soft/r_math.d \
./Example/User/CM7/engine/ref/soft/r_misc.d \
./Example/User/CM7/engine/ref/soft/r_part.d \
./Example/User/CM7/engine/ref/soft/r_polyse.d \
./Example/User/CM7/engine/ref/soft/r_rast.d \
./Example/User/CM7/engine/ref/soft/r_scan.d \
./Example/User/CM7/engine/ref/soft/r_sprite.d \
./Example/User/CM7/engine/ref/soft/r_studio.d \
./Example/User/CM7/engine/ref/soft/r_surf.d \
./Example/User/CM7/engine/ref/soft/r_trialias.d \
./Example/User/CM7/engine/ref/soft/r_triapi.d \
./Example/User/CM7/engine/ref/soft/r_vgui.d 

OBJS += \
./Example/User/CM7/engine/ref/soft/r_aclip.o \
./Example/User/CM7/engine/ref/soft/r_beams.o \
./Example/User/CM7/engine/ref/soft/r_bsp.o \
./Example/User/CM7/engine/ref/soft/r_context.o \
./Example/User/CM7/engine/ref/soft/r_decals.o \
./Example/User/CM7/engine/ref/soft/r_draw.o \
./Example/User/CM7/engine/ref/soft/r_edge.o \
./Example/User/CM7/engine/ref/soft/r_glblit.o \
./Example/User/CM7/engine/ref/soft/r_image.o \
./Example/User/CM7/engine/ref/soft/r_light.o \
./Example/User/CM7/engine/ref/soft/r_main.o \
./Example/User/CM7/engine/ref/soft/r_math.o \
./Example/User/CM7/engine/ref/soft/r_misc.o \
./Example/User/CM7/engine/ref/soft/r_part.o \
./Example/User/CM7/engine/ref/soft/r_polyse.o \
./Example/User/CM7/engine/ref/soft/r_rast.o \
./Example/User/CM7/engine/ref/soft/r_scan.o \
./Example/User/CM7/engine/ref/soft/r_sprite.o \
./Example/User/CM7/engine/ref/soft/r_studio.o \
./Example/User/CM7/engine/ref/soft/r_surf.o \
./Example/User/CM7/engine/ref/soft/r_trialias.o \
./Example/User/CM7/engine/ref/soft/r_triapi.o \
./Example/User/CM7/engine/ref/soft/r_vgui.o 


# Each subdirectory must supply rules for building sources it contributes
Example/User/CM7/engine/ref/soft/%.o Example/User/CM7/engine/ref/soft/%.su Example/User/CM7/engine/ref/soft/%.cyclo: ../Example/User/CM7/engine/ref/soft/%.c Example/User/CM7/engine/ref/soft/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -DTS_MULTI_TOUCH_SUPPORTED -c -I../../../CM7/Inc -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Example/User/CM7" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/App" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/Target" -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32H747I-DISCO -I../../../Drivers/BSP/Components/Common -I../../../Utilities/lcd -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fms-extensions -I../Example/User/CM7/common/ -I../Example/User/CM7/engine/ -I../Example/User/CM7/engine/client/ -I../Example/User/CM7/engine/client/vgui/ -I../Example/User/CM7/engine/common/ -I../Example/User/CM7/engine/common/imagelib/ -I../Example/User/CM7/engine/filesystem/ -I../Example/User/CM7/engine/mainui/ -I../Example/User/CM7/engine/mainui/controls/ -I../Example/User/CM7/engine/mainui/font/ -I../Example/User/CM7/engine/mainui/menus/ -I../Example/User/CM7/engine/mainui/miniutl/ -I../Example/User/CM7/engine/mainui/model/ -I../Example/User/CM7/engine/opus/celt/ -I../Example/User/CM7/engine/opus/include/ -I../Example/User/CM7/engine/opus/silk/ -I../Example/User/CM7/engine/opus/silk/float/ -I../Example/User/CM7/engine/platform/ -I../Example/User/CM7/engine/ref/soft/ -I../Example/User/CM7/engine/sdk/cl_dll/ -I../Example/User/CM7/engine/sdk/dlls/ -I../Example/User/CM7/engine/sdk/pm_shared/ -I../Example/User/CM7/engine/server/ -I../Example/User/CM7/pm_shared/ -I../Example/User/CM7/public/ -D__GNU_VISIBLE=1 -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp  -D_snprintf=snprintf  -D_vsnprintf=vsnprintf  -D_LINUX  -DLINUX -DXASH_NO_LIBDL=1 -DXASH_NO_ASYNC_NS_RESOLVE=1 -DFLOAT_APPROX=1 -DOPUS_BUILD=1 -DXASH_GAMEDIR="valve" -DMAINUI_USE_CUSTOM_FONT_RENDER=1 -DSTDINT_H="<stdint.h>" -DHAVE_STDINT_H=1 -DPSAPI_VERSION=1 -DDBGHELP=1 -DALLOCA_H="<alloca.h>" -DXASH_REF_SOFT_ENABLED=1 -DCUSTOM_MODES=1 -DSINGLE_BINARY=1 -DHAVE_MALLOC_H=1 -DUSE_ALLOCA=1 -DPACKAGE_VERSION="1.3.1" -DXASH_LOW_MEMORY=2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Example-2f-User-2f-CM7-2f-engine-2f-ref-2f-soft

clean-Example-2f-User-2f-CM7-2f-engine-2f-ref-2f-soft:
	-$(RM) ./Example/User/CM7/engine/ref/soft/r_aclip.cyclo ./Example/User/CM7/engine/ref/soft/r_aclip.d ./Example/User/CM7/engine/ref/soft/r_aclip.o ./Example/User/CM7/engine/ref/soft/r_aclip.su ./Example/User/CM7/engine/ref/soft/r_beams.cyclo ./Example/User/CM7/engine/ref/soft/r_beams.d ./Example/User/CM7/engine/ref/soft/r_beams.o ./Example/User/CM7/engine/ref/soft/r_beams.su ./Example/User/CM7/engine/ref/soft/r_bsp.cyclo ./Example/User/CM7/engine/ref/soft/r_bsp.d ./Example/User/CM7/engine/ref/soft/r_bsp.o ./Example/User/CM7/engine/ref/soft/r_bsp.su ./Example/User/CM7/engine/ref/soft/r_context.cyclo ./Example/User/CM7/engine/ref/soft/r_context.d ./Example/User/CM7/engine/ref/soft/r_context.o ./Example/User/CM7/engine/ref/soft/r_context.su ./Example/User/CM7/engine/ref/soft/r_decals.cyclo ./Example/User/CM7/engine/ref/soft/r_decals.d ./Example/User/CM7/engine/ref/soft/r_decals.o ./Example/User/CM7/engine/ref/soft/r_decals.su ./Example/User/CM7/engine/ref/soft/r_draw.cyclo ./Example/User/CM7/engine/ref/soft/r_draw.d ./Example/User/CM7/engine/ref/soft/r_draw.o ./Example/User/CM7/engine/ref/soft/r_draw.su ./Example/User/CM7/engine/ref/soft/r_edge.cyclo ./Example/User/CM7/engine/ref/soft/r_edge.d ./Example/User/CM7/engine/ref/soft/r_edge.o ./Example/User/CM7/engine/ref/soft/r_edge.su ./Example/User/CM7/engine/ref/soft/r_glblit.cyclo ./Example/User/CM7/engine/ref/soft/r_glblit.d ./Example/User/CM7/engine/ref/soft/r_glblit.o ./Example/User/CM7/engine/ref/soft/r_glblit.su ./Example/User/CM7/engine/ref/soft/r_image.cyclo ./Example/User/CM7/engine/ref/soft/r_image.d ./Example/User/CM7/engine/ref/soft/r_image.o ./Example/User/CM7/engine/ref/soft/r_image.su ./Example/User/CM7/engine/ref/soft/r_light.cyclo ./Example/User/CM7/engine/ref/soft/r_light.d ./Example/User/CM7/engine/ref/soft/r_light.o ./Example/User/CM7/engine/ref/soft/r_light.su ./Example/User/CM7/engine/ref/soft/r_main.cyclo ./Example/User/CM7/engine/ref/soft/r_main.d ./Example/User/CM7/engine/ref/soft/r_main.o ./Example/User/CM7/engine/ref/soft/r_main.su ./Example/User/CM7/engine/ref/soft/r_math.cyclo ./Example/User/CM7/engine/ref/soft/r_math.d ./Example/User/CM7/engine/ref/soft/r_math.o ./Example/User/CM7/engine/ref/soft/r_math.su ./Example/User/CM7/engine/ref/soft/r_misc.cyclo ./Example/User/CM7/engine/ref/soft/r_misc.d ./Example/User/CM7/engine/ref/soft/r_misc.o ./Example/User/CM7/engine/ref/soft/r_misc.su ./Example/User/CM7/engine/ref/soft/r_part.cyclo ./Example/User/CM7/engine/ref/soft/r_part.d ./Example/User/CM7/engine/ref/soft/r_part.o ./Example/User/CM7/engine/ref/soft/r_part.su ./Example/User/CM7/engine/ref/soft/r_polyse.cyclo ./Example/User/CM7/engine/ref/soft/r_polyse.d ./Example/User/CM7/engine/ref/soft/r_polyse.o ./Example/User/CM7/engine/ref/soft/r_polyse.su ./Example/User/CM7/engine/ref/soft/r_rast.cyclo ./Example/User/CM7/engine/ref/soft/r_rast.d ./Example/User/CM7/engine/ref/soft/r_rast.o ./Example/User/CM7/engine/ref/soft/r_rast.su ./Example/User/CM7/engine/ref/soft/r_scan.cyclo ./Example/User/CM7/engine/ref/soft/r_scan.d ./Example/User/CM7/engine/ref/soft/r_scan.o ./Example/User/CM7/engine/ref/soft/r_scan.su ./Example/User/CM7/engine/ref/soft/r_sprite.cyclo ./Example/User/CM7/engine/ref/soft/r_sprite.d ./Example/User/CM7/engine/ref/soft/r_sprite.o ./Example/User/CM7/engine/ref/soft/r_sprite.su ./Example/User/CM7/engine/ref/soft/r_studio.cyclo ./Example/User/CM7/engine/ref/soft/r_studio.d ./Example/User/CM7/engine/ref/soft/r_studio.o ./Example/User/CM7/engine/ref/soft/r_studio.su ./Example/User/CM7/engine/ref/soft/r_surf.cyclo ./Example/User/CM7/engine/ref/soft/r_surf.d ./Example/User/CM7/engine/ref/soft/r_surf.o ./Example/User/CM7/engine/ref/soft/r_surf.su ./Example/User/CM7/engine/ref/soft/r_trialias.cyclo ./Example/User/CM7/engine/ref/soft/r_trialias.d ./Example/User/CM7/engine/ref/soft/r_trialias.o ./Example/User/CM7/engine/ref/soft/r_trialias.su ./Example/User/CM7/engine/ref/soft/r_triapi.cyclo ./Example/User/CM7/engine/ref/soft/r_triapi.d ./Example/User/CM7/engine/ref/soft/r_triapi.o ./Example/User/CM7/engine/ref/soft/r_triapi.su ./Example/User/CM7/engine/ref/soft/r_vgui.cyclo ./Example/User/CM7/engine/ref/soft/r_vgui.d ./Example/User/CM7/engine/ref/soft/r_vgui.o ./Example/User/CM7/engine/ref/soft/r_vgui.su

.PHONY: clean-Example-2f-User-2f-CM7-2f-engine-2f-ref-2f-soft

