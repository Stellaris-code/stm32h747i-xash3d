################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/subdir.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Example/User/Startup/subdir.mk
-include Example/User/CM7/public/subdir.mk
-include Example/User/CM7/engine/server/subdir.mk
-include Example/User/CM7/engine/sdk/pm_shared/subdir.mk
-include Example/User/CM7/engine/sdk/dlls/subdir.mk
-include Example/User/CM7/engine/sdk/cl_dll/subdir.mk
-include Example/User/CM7/engine/ref/soft/subdir.mk
-include Example/User/CM7/engine/platform/stm32/subdir.mk
-include Example/User/CM7/engine/platform/fatfs/subdir.mk
-include Example/User/CM7/engine/opus/src/subdir.mk
-include Example/User/CM7/engine/opus/silk/float/subdir.mk
-include Example/User/CM7/engine/opus/silk/subdir.mk
-include Example/User/CM7/engine/opus/celt/subdir.mk
-include Example/User/CM7/engine/mainui/miniutl/subdir.mk
-include Example/User/CM7/engine/mainui/menus/dynamic/subdir.mk
-include Example/User/CM7/engine/mainui/menus/subdir.mk
-include Example/User/CM7/engine/mainui/font/subdir.mk
-include Example/User/CM7/engine/mainui/controls/subdir.mk
-include Example/User/CM7/engine/mainui/subdir.mk
-include Example/User/CM7/engine/filesystem/subdir.mk
-include Example/User/CM7/engine/common/soundlib/libmpg/subdir.mk
-include Example/User/CM7/engine/common/soundlib/subdir.mk
-include Example/User/CM7/engine/common/imagelib/subdir.mk
-include Example/User/CM7/engine/common/subdir.mk
-include Example/User/CM7/engine/client/vgui/subdir.mk
-include Example/User/CM7/engine/client/avi/subdir.mk
-include Example/User/CM7/engine/client/subdir.mk
-include Example/User/CM7/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/STM32H747I-DISCO/subdir.mk
-include Drivers/BSP/Components/wm8994/subdir.mk
-include Drivers/BSP/Components/ov9655/subdir.mk
-include Drivers/BSP/Components/ov5640/subdir.mk
-include Drivers/BSP/Components/otm8009a/subdir.mk
-include Drivers/BSP/Components/mt25tl01g/subdir.mk
-include Drivers/BSP/Components/is42s32800j/subdir.mk
-include Drivers/BSP/Components/ft6x06/subdir.mk
-include Drivers/BSP/Components/adv7533/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BSP_CM7
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
BSP_CM7.elf \

MAP_FILES += \
BSP_CM7.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BSP_CM7.list \


# All Target
all: main-build

# Main-build Target
main-build: BSP_CM7.elf secondary-outputs

# Tool invocations
BSP_CM7.elf BSP_CM7.map: $(OBJS) $(USER_OBJS) C:\Users\Ya2nb\Travail\MI11\stm32h747i-xash3d\BSP\STM32CubeIDE\CM7\STM32H747XIHX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "BSP_CM7.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\Ya2nb\Travail\MI11\stm32h747i-xash3d\BSP\STM32CubeIDE\CM7\STM32H747XIHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BSP_CM7.map" -Wl,--gc-sections -static -L"C:\Users\Ya2nb\Travail\MI11\stm32h747i-xash3d\BSP\STM32CubeIDE\CM7\Middlewares\ST\STM32_Audio\Addons\PDM\Lib" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BSP_CM7.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BSP_CM7.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) BSP_CM7.elf BSP_CM7.list BSP_CM7.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
