################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Example/User/CM7/engine/opus/silk/A2NLSF.c \
../Example/User/CM7/engine/opus/silk/CNG.c \
../Example/User/CM7/engine/opus/silk/HP_variable_cutoff.c \
../Example/User/CM7/engine/opus/silk/LPC_analysis_filter.c \
../Example/User/CM7/engine/opus/silk/LPC_fit.c \
../Example/User/CM7/engine/opus/silk/LPC_inv_pred_gain.c \
../Example/User/CM7/engine/opus/silk/LP_variable_cutoff.c \
../Example/User/CM7/engine/opus/silk/NLSF2A.c \
../Example/User/CM7/engine/opus/silk/NLSF_VQ.c \
../Example/User/CM7/engine/opus/silk/NLSF_VQ_weights_laroia.c \
../Example/User/CM7/engine/opus/silk/NLSF_decode.c \
../Example/User/CM7/engine/opus/silk/NLSF_del_dec_quant.c \
../Example/User/CM7/engine/opus/silk/NLSF_encode.c \
../Example/User/CM7/engine/opus/silk/NLSF_stabilize.c \
../Example/User/CM7/engine/opus/silk/NLSF_unpack.c \
../Example/User/CM7/engine/opus/silk/NSQ.c \
../Example/User/CM7/engine/opus/silk/NSQ_del_dec.c \
../Example/User/CM7/engine/opus/silk/PLC.c \
../Example/User/CM7/engine/opus/silk/VAD.c \
../Example/User/CM7/engine/opus/silk/VQ_WMat_EC.c \
../Example/User/CM7/engine/opus/silk/ana_filt_bank_1.c \
../Example/User/CM7/engine/opus/silk/biquad_alt.c \
../Example/User/CM7/engine/opus/silk/bwexpander.c \
../Example/User/CM7/engine/opus/silk/bwexpander_32.c \
../Example/User/CM7/engine/opus/silk/check_control_input.c \
../Example/User/CM7/engine/opus/silk/code_signs.c \
../Example/User/CM7/engine/opus/silk/control_SNR.c \
../Example/User/CM7/engine/opus/silk/control_audio_bandwidth.c \
../Example/User/CM7/engine/opus/silk/control_codec.c \
../Example/User/CM7/engine/opus/silk/debug.c \
../Example/User/CM7/engine/opus/silk/dec_API.c \
../Example/User/CM7/engine/opus/silk/decode_core.c \
../Example/User/CM7/engine/opus/silk/decode_frame.c \
../Example/User/CM7/engine/opus/silk/decode_indices.c \
../Example/User/CM7/engine/opus/silk/decode_parameters.c \
../Example/User/CM7/engine/opus/silk/decode_pitch.c \
../Example/User/CM7/engine/opus/silk/decode_pulses.c \
../Example/User/CM7/engine/opus/silk/decoder_set_fs.c \
../Example/User/CM7/engine/opus/silk/enc_API.c \
../Example/User/CM7/engine/opus/silk/encode_indices.c \
../Example/User/CM7/engine/opus/silk/encode_pulses.c \
../Example/User/CM7/engine/opus/silk/gain_quant.c \
../Example/User/CM7/engine/opus/silk/init_decoder.c \
../Example/User/CM7/engine/opus/silk/init_encoder.c \
../Example/User/CM7/engine/opus/silk/inner_prod_aligned.c \
../Example/User/CM7/engine/opus/silk/interpolate.c \
../Example/User/CM7/engine/opus/silk/lin2log.c \
../Example/User/CM7/engine/opus/silk/log2lin.c \
../Example/User/CM7/engine/opus/silk/pitch_est_tables.c \
../Example/User/CM7/engine/opus/silk/process_NLSFs.c \
../Example/User/CM7/engine/opus/silk/quant_LTP_gains.c \
../Example/User/CM7/engine/opus/silk/resampler.c \
../Example/User/CM7/engine/opus/silk/resampler_down2.c \
../Example/User/CM7/engine/opus/silk/resampler_down2_3.c \
../Example/User/CM7/engine/opus/silk/resampler_private_AR2.c \
../Example/User/CM7/engine/opus/silk/resampler_private_IIR_FIR.c \
../Example/User/CM7/engine/opus/silk/resampler_private_down_FIR.c \
../Example/User/CM7/engine/opus/silk/resampler_private_up2_HQ.c \
../Example/User/CM7/engine/opus/silk/resampler_rom.c \
../Example/User/CM7/engine/opus/silk/shell_coder.c \
../Example/User/CM7/engine/opus/silk/sigm_Q15.c \
../Example/User/CM7/engine/opus/silk/sort.c \
../Example/User/CM7/engine/opus/silk/stereo_LR_to_MS.c \
../Example/User/CM7/engine/opus/silk/stereo_MS_to_LR.c \
../Example/User/CM7/engine/opus/silk/stereo_decode_pred.c \
../Example/User/CM7/engine/opus/silk/stereo_encode_pred.c \
../Example/User/CM7/engine/opus/silk/stereo_find_predictor.c \
../Example/User/CM7/engine/opus/silk/stereo_quant_pred.c \
../Example/User/CM7/engine/opus/silk/sum_sqr_shift.c \
../Example/User/CM7/engine/opus/silk/table_LSF_cos.c \
../Example/User/CM7/engine/opus/silk/tables_LTP.c \
../Example/User/CM7/engine/opus/silk/tables_NLSF_CB_NB_MB.c \
../Example/User/CM7/engine/opus/silk/tables_NLSF_CB_WB.c \
../Example/User/CM7/engine/opus/silk/tables_gain.c \
../Example/User/CM7/engine/opus/silk/tables_other.c \
../Example/User/CM7/engine/opus/silk/tables_pitch_lag.c \
../Example/User/CM7/engine/opus/silk/tables_pulses_per_block.c 

C_DEPS += \
./Example/User/CM7/engine/opus/silk/A2NLSF.d \
./Example/User/CM7/engine/opus/silk/CNG.d \
./Example/User/CM7/engine/opus/silk/HP_variable_cutoff.d \
./Example/User/CM7/engine/opus/silk/LPC_analysis_filter.d \
./Example/User/CM7/engine/opus/silk/LPC_fit.d \
./Example/User/CM7/engine/opus/silk/LPC_inv_pred_gain.d \
./Example/User/CM7/engine/opus/silk/LP_variable_cutoff.d \
./Example/User/CM7/engine/opus/silk/NLSF2A.d \
./Example/User/CM7/engine/opus/silk/NLSF_VQ.d \
./Example/User/CM7/engine/opus/silk/NLSF_VQ_weights_laroia.d \
./Example/User/CM7/engine/opus/silk/NLSF_decode.d \
./Example/User/CM7/engine/opus/silk/NLSF_del_dec_quant.d \
./Example/User/CM7/engine/opus/silk/NLSF_encode.d \
./Example/User/CM7/engine/opus/silk/NLSF_stabilize.d \
./Example/User/CM7/engine/opus/silk/NLSF_unpack.d \
./Example/User/CM7/engine/opus/silk/NSQ.d \
./Example/User/CM7/engine/opus/silk/NSQ_del_dec.d \
./Example/User/CM7/engine/opus/silk/PLC.d \
./Example/User/CM7/engine/opus/silk/VAD.d \
./Example/User/CM7/engine/opus/silk/VQ_WMat_EC.d \
./Example/User/CM7/engine/opus/silk/ana_filt_bank_1.d \
./Example/User/CM7/engine/opus/silk/biquad_alt.d \
./Example/User/CM7/engine/opus/silk/bwexpander.d \
./Example/User/CM7/engine/opus/silk/bwexpander_32.d \
./Example/User/CM7/engine/opus/silk/check_control_input.d \
./Example/User/CM7/engine/opus/silk/code_signs.d \
./Example/User/CM7/engine/opus/silk/control_SNR.d \
./Example/User/CM7/engine/opus/silk/control_audio_bandwidth.d \
./Example/User/CM7/engine/opus/silk/control_codec.d \
./Example/User/CM7/engine/opus/silk/debug.d \
./Example/User/CM7/engine/opus/silk/dec_API.d \
./Example/User/CM7/engine/opus/silk/decode_core.d \
./Example/User/CM7/engine/opus/silk/decode_frame.d \
./Example/User/CM7/engine/opus/silk/decode_indices.d \
./Example/User/CM7/engine/opus/silk/decode_parameters.d \
./Example/User/CM7/engine/opus/silk/decode_pitch.d \
./Example/User/CM7/engine/opus/silk/decode_pulses.d \
./Example/User/CM7/engine/opus/silk/decoder_set_fs.d \
./Example/User/CM7/engine/opus/silk/enc_API.d \
./Example/User/CM7/engine/opus/silk/encode_indices.d \
./Example/User/CM7/engine/opus/silk/encode_pulses.d \
./Example/User/CM7/engine/opus/silk/gain_quant.d \
./Example/User/CM7/engine/opus/silk/init_decoder.d \
./Example/User/CM7/engine/opus/silk/init_encoder.d \
./Example/User/CM7/engine/opus/silk/inner_prod_aligned.d \
./Example/User/CM7/engine/opus/silk/interpolate.d \
./Example/User/CM7/engine/opus/silk/lin2log.d \
./Example/User/CM7/engine/opus/silk/log2lin.d \
./Example/User/CM7/engine/opus/silk/pitch_est_tables.d \
./Example/User/CM7/engine/opus/silk/process_NLSFs.d \
./Example/User/CM7/engine/opus/silk/quant_LTP_gains.d \
./Example/User/CM7/engine/opus/silk/resampler.d \
./Example/User/CM7/engine/opus/silk/resampler_down2.d \
./Example/User/CM7/engine/opus/silk/resampler_down2_3.d \
./Example/User/CM7/engine/opus/silk/resampler_private_AR2.d \
./Example/User/CM7/engine/opus/silk/resampler_private_IIR_FIR.d \
./Example/User/CM7/engine/opus/silk/resampler_private_down_FIR.d \
./Example/User/CM7/engine/opus/silk/resampler_private_up2_HQ.d \
./Example/User/CM7/engine/opus/silk/resampler_rom.d \
./Example/User/CM7/engine/opus/silk/shell_coder.d \
./Example/User/CM7/engine/opus/silk/sigm_Q15.d \
./Example/User/CM7/engine/opus/silk/sort.d \
./Example/User/CM7/engine/opus/silk/stereo_LR_to_MS.d \
./Example/User/CM7/engine/opus/silk/stereo_MS_to_LR.d \
./Example/User/CM7/engine/opus/silk/stereo_decode_pred.d \
./Example/User/CM7/engine/opus/silk/stereo_encode_pred.d \
./Example/User/CM7/engine/opus/silk/stereo_find_predictor.d \
./Example/User/CM7/engine/opus/silk/stereo_quant_pred.d \
./Example/User/CM7/engine/opus/silk/sum_sqr_shift.d \
./Example/User/CM7/engine/opus/silk/table_LSF_cos.d \
./Example/User/CM7/engine/opus/silk/tables_LTP.d \
./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_NB_MB.d \
./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_WB.d \
./Example/User/CM7/engine/opus/silk/tables_gain.d \
./Example/User/CM7/engine/opus/silk/tables_other.d \
./Example/User/CM7/engine/opus/silk/tables_pitch_lag.d \
./Example/User/CM7/engine/opus/silk/tables_pulses_per_block.d 

OBJS += \
./Example/User/CM7/engine/opus/silk/A2NLSF.o \
./Example/User/CM7/engine/opus/silk/CNG.o \
./Example/User/CM7/engine/opus/silk/HP_variable_cutoff.o \
./Example/User/CM7/engine/opus/silk/LPC_analysis_filter.o \
./Example/User/CM7/engine/opus/silk/LPC_fit.o \
./Example/User/CM7/engine/opus/silk/LPC_inv_pred_gain.o \
./Example/User/CM7/engine/opus/silk/LP_variable_cutoff.o \
./Example/User/CM7/engine/opus/silk/NLSF2A.o \
./Example/User/CM7/engine/opus/silk/NLSF_VQ.o \
./Example/User/CM7/engine/opus/silk/NLSF_VQ_weights_laroia.o \
./Example/User/CM7/engine/opus/silk/NLSF_decode.o \
./Example/User/CM7/engine/opus/silk/NLSF_del_dec_quant.o \
./Example/User/CM7/engine/opus/silk/NLSF_encode.o \
./Example/User/CM7/engine/opus/silk/NLSF_stabilize.o \
./Example/User/CM7/engine/opus/silk/NLSF_unpack.o \
./Example/User/CM7/engine/opus/silk/NSQ.o \
./Example/User/CM7/engine/opus/silk/NSQ_del_dec.o \
./Example/User/CM7/engine/opus/silk/PLC.o \
./Example/User/CM7/engine/opus/silk/VAD.o \
./Example/User/CM7/engine/opus/silk/VQ_WMat_EC.o \
./Example/User/CM7/engine/opus/silk/ana_filt_bank_1.o \
./Example/User/CM7/engine/opus/silk/biquad_alt.o \
./Example/User/CM7/engine/opus/silk/bwexpander.o \
./Example/User/CM7/engine/opus/silk/bwexpander_32.o \
./Example/User/CM7/engine/opus/silk/check_control_input.o \
./Example/User/CM7/engine/opus/silk/code_signs.o \
./Example/User/CM7/engine/opus/silk/control_SNR.o \
./Example/User/CM7/engine/opus/silk/control_audio_bandwidth.o \
./Example/User/CM7/engine/opus/silk/control_codec.o \
./Example/User/CM7/engine/opus/silk/debug.o \
./Example/User/CM7/engine/opus/silk/dec_API.o \
./Example/User/CM7/engine/opus/silk/decode_core.o \
./Example/User/CM7/engine/opus/silk/decode_frame.o \
./Example/User/CM7/engine/opus/silk/decode_indices.o \
./Example/User/CM7/engine/opus/silk/decode_parameters.o \
./Example/User/CM7/engine/opus/silk/decode_pitch.o \
./Example/User/CM7/engine/opus/silk/decode_pulses.o \
./Example/User/CM7/engine/opus/silk/decoder_set_fs.o \
./Example/User/CM7/engine/opus/silk/enc_API.o \
./Example/User/CM7/engine/opus/silk/encode_indices.o \
./Example/User/CM7/engine/opus/silk/encode_pulses.o \
./Example/User/CM7/engine/opus/silk/gain_quant.o \
./Example/User/CM7/engine/opus/silk/init_decoder.o \
./Example/User/CM7/engine/opus/silk/init_encoder.o \
./Example/User/CM7/engine/opus/silk/inner_prod_aligned.o \
./Example/User/CM7/engine/opus/silk/interpolate.o \
./Example/User/CM7/engine/opus/silk/lin2log.o \
./Example/User/CM7/engine/opus/silk/log2lin.o \
./Example/User/CM7/engine/opus/silk/pitch_est_tables.o \
./Example/User/CM7/engine/opus/silk/process_NLSFs.o \
./Example/User/CM7/engine/opus/silk/quant_LTP_gains.o \
./Example/User/CM7/engine/opus/silk/resampler.o \
./Example/User/CM7/engine/opus/silk/resampler_down2.o \
./Example/User/CM7/engine/opus/silk/resampler_down2_3.o \
./Example/User/CM7/engine/opus/silk/resampler_private_AR2.o \
./Example/User/CM7/engine/opus/silk/resampler_private_IIR_FIR.o \
./Example/User/CM7/engine/opus/silk/resampler_private_down_FIR.o \
./Example/User/CM7/engine/opus/silk/resampler_private_up2_HQ.o \
./Example/User/CM7/engine/opus/silk/resampler_rom.o \
./Example/User/CM7/engine/opus/silk/shell_coder.o \
./Example/User/CM7/engine/opus/silk/sigm_Q15.o \
./Example/User/CM7/engine/opus/silk/sort.o \
./Example/User/CM7/engine/opus/silk/stereo_LR_to_MS.o \
./Example/User/CM7/engine/opus/silk/stereo_MS_to_LR.o \
./Example/User/CM7/engine/opus/silk/stereo_decode_pred.o \
./Example/User/CM7/engine/opus/silk/stereo_encode_pred.o \
./Example/User/CM7/engine/opus/silk/stereo_find_predictor.o \
./Example/User/CM7/engine/opus/silk/stereo_quant_pred.o \
./Example/User/CM7/engine/opus/silk/sum_sqr_shift.o \
./Example/User/CM7/engine/opus/silk/table_LSF_cos.o \
./Example/User/CM7/engine/opus/silk/tables_LTP.o \
./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_NB_MB.o \
./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_WB.o \
./Example/User/CM7/engine/opus/silk/tables_gain.o \
./Example/User/CM7/engine/opus/silk/tables_other.o \
./Example/User/CM7/engine/opus/silk/tables_pitch_lag.o \
./Example/User/CM7/engine/opus/silk/tables_pulses_per_block.o 


# Each subdirectory must supply rules for building sources it contributes
Example/User/CM7/engine/opus/silk/%.o Example/User/CM7/engine/opus/silk/%.su Example/User/CM7/engine/opus/silk/%.cyclo: ../Example/User/CM7/engine/opus/silk/%.c Example/User/CM7/engine/opus/silk/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_STM32H747I_DISCO -DUSE_HAL_DRIVER -DSTM32H747xx -DCORE_CM7 -DTS_MULTI_TOUCH_SUPPORTED -c -I../../../CM7/Inc -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Example/User/CM7" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/App" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Ya2nb/Travail/MI11/stm32h747i-xash3d/BSP/STM32CubeIDE/CM7/USB_DEVICE/Target" -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32H747I-DISCO -I../../../Drivers/BSP/Components/Common -I../../../Utilities/lcd -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fms-extensions -I../Example/User/CM7/common/ -I../Example/User/CM7/engine/ -I../Example/User/CM7/engine/client/ -I../Example/User/CM7/engine/client/vgui/ -I../Example/User/CM7/engine/common/ -I../Example/User/CM7/engine/common/imagelib/ -I../Example/User/CM7/engine/filesystem/ -I../Example/User/CM7/engine/mainui/ -I../Example/User/CM7/engine/mainui/controls/ -I../Example/User/CM7/engine/mainui/font/ -I../Example/User/CM7/engine/mainui/menus/ -I../Example/User/CM7/engine/mainui/miniutl/ -I../Example/User/CM7/engine/mainui/model/ -I../Example/User/CM7/engine/opus/celt/ -I../Example/User/CM7/engine/opus/include/ -I../Example/User/CM7/engine/opus/silk/ -I../Example/User/CM7/engine/opus/silk/float/ -I../Example/User/CM7/engine/platform/ -I../Example/User/CM7/engine/ref/soft/ -I../Example/User/CM7/engine/sdk/cl_dll/ -I../Example/User/CM7/engine/sdk/dlls/ -I../Example/User/CM7/engine/sdk/pm_shared/ -I../Example/User/CM7/engine/server/ -I../Example/User/CM7/pm_shared/ -I../Example/User/CM7/public/ -D__GNU_VISIBLE=1 -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp  -D_snprintf=snprintf  -D_vsnprintf=vsnprintf  -D_LINUX  -DLINUX -DXASH_NO_LIBDL=1 -DXASH_NO_ASYNC_NS_RESOLVE=1 -DFLOAT_APPROX=1 -DOPUS_BUILD=1 -DXASH_GAMEDIR="valve" -DMAINUI_USE_CUSTOM_FONT_RENDER=1 -DSTDINT_H="<stdint.h>" -DHAVE_STDINT_H=1 -DPSAPI_VERSION=1 -DDBGHELP=1 -DALLOCA_H="<alloca.h>" -DXASH_REF_SOFT_ENABLED=1 -DCUSTOM_MODES=1 -DSINGLE_BINARY=1 -DHAVE_MALLOC_H=1 -DUSE_ALLOCA=1 -DPACKAGE_VERSION="1.3.1" -DXASH_LOW_MEMORY=2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Example-2f-User-2f-CM7-2f-engine-2f-opus-2f-silk

clean-Example-2f-User-2f-CM7-2f-engine-2f-opus-2f-silk:
	-$(RM) ./Example/User/CM7/engine/opus/silk/A2NLSF.cyclo ./Example/User/CM7/engine/opus/silk/A2NLSF.d ./Example/User/CM7/engine/opus/silk/A2NLSF.o ./Example/User/CM7/engine/opus/silk/A2NLSF.su ./Example/User/CM7/engine/opus/silk/CNG.cyclo ./Example/User/CM7/engine/opus/silk/CNG.d ./Example/User/CM7/engine/opus/silk/CNG.o ./Example/User/CM7/engine/opus/silk/CNG.su ./Example/User/CM7/engine/opus/silk/HP_variable_cutoff.cyclo ./Example/User/CM7/engine/opus/silk/HP_variable_cutoff.d ./Example/User/CM7/engine/opus/silk/HP_variable_cutoff.o ./Example/User/CM7/engine/opus/silk/HP_variable_cutoff.su ./Example/User/CM7/engine/opus/silk/LPC_analysis_filter.cyclo ./Example/User/CM7/engine/opus/silk/LPC_analysis_filter.d ./Example/User/CM7/engine/opus/silk/LPC_analysis_filter.o ./Example/User/CM7/engine/opus/silk/LPC_analysis_filter.su ./Example/User/CM7/engine/opus/silk/LPC_fit.cyclo ./Example/User/CM7/engine/opus/silk/LPC_fit.d ./Example/User/CM7/engine/opus/silk/LPC_fit.o ./Example/User/CM7/engine/opus/silk/LPC_fit.su ./Example/User/CM7/engine/opus/silk/LPC_inv_pred_gain.cyclo ./Example/User/CM7/engine/opus/silk/LPC_inv_pred_gain.d ./Example/User/CM7/engine/opus/silk/LPC_inv_pred_gain.o ./Example/User/CM7/engine/opus/silk/LPC_inv_pred_gain.su ./Example/User/CM7/engine/opus/silk/LP_variable_cutoff.cyclo ./Example/User/CM7/engine/opus/silk/LP_variable_cutoff.d ./Example/User/CM7/engine/opus/silk/LP_variable_cutoff.o ./Example/User/CM7/engine/opus/silk/LP_variable_cutoff.su ./Example/User/CM7/engine/opus/silk/NLSF2A.cyclo ./Example/User/CM7/engine/opus/silk/NLSF2A.d ./Example/User/CM7/engine/opus/silk/NLSF2A.o ./Example/User/CM7/engine/opus/silk/NLSF2A.su ./Example/User/CM7/engine/opus/silk/NLSF_VQ.cyclo ./Example/User/CM7/engine/opus/silk/NLSF_VQ.d ./Example/User/CM7/engine/opus/silk/NLSF_VQ.o ./Example/User/CM7/engine/opus/silk/NLSF_VQ.su ./Example/User/CM7/engine/opus/silk/NLSF_VQ_weights_laroia.cyclo ./Example/User/CM7/engine/opus/silk/NLSF_VQ_weights_laroia.d ./Example/User/CM7/engine/opus/silk/NLSF_VQ_weights_laroia.o ./Example/User/CM7/engine/opus/silk/NLSF_VQ_weights_laroia.su ./Example/User/CM7/engine/opus/silk/NLSF_decode.cyclo ./Example/User/CM7/engine/opus/silk/NLSF_decode.d ./Example/User/CM7/engine/opus/silk/NLSF_decode.o ./Example/User/CM7/engine/opus/silk/NLSF_decode.su ./Example/User/CM7/engine/opus/silk/NLSF_del_dec_quant.cyclo ./Example/User/CM7/engine/opus/silk/NLSF_del_dec_quant.d ./Example/User/CM7/engine/opus/silk/NLSF_del_dec_quant.o ./Example/User/CM7/engine/opus/silk/NLSF_del_dec_quant.su ./Example/User/CM7/engine/opus/silk/NLSF_encode.cyclo ./Example/User/CM7/engine/opus/silk/NLSF_encode.d ./Example/User/CM7/engine/opus/silk/NLSF_encode.o ./Example/User/CM7/engine/opus/silk/NLSF_encode.su ./Example/User/CM7/engine/opus/silk/NLSF_stabilize.cyclo ./Example/User/CM7/engine/opus/silk/NLSF_stabilize.d ./Example/User/CM7/engine/opus/silk/NLSF_stabilize.o ./Example/User/CM7/engine/opus/silk/NLSF_stabilize.su ./Example/User/CM7/engine/opus/silk/NLSF_unpack.cyclo ./Example/User/CM7/engine/opus/silk/NLSF_unpack.d ./Example/User/CM7/engine/opus/silk/NLSF_unpack.o ./Example/User/CM7/engine/opus/silk/NLSF_unpack.su ./Example/User/CM7/engine/opus/silk/NSQ.cyclo ./Example/User/CM7/engine/opus/silk/NSQ.d ./Example/User/CM7/engine/opus/silk/NSQ.o ./Example/User/CM7/engine/opus/silk/NSQ.su ./Example/User/CM7/engine/opus/silk/NSQ_del_dec.cyclo ./Example/User/CM7/engine/opus/silk/NSQ_del_dec.d ./Example/User/CM7/engine/opus/silk/NSQ_del_dec.o ./Example/User/CM7/engine/opus/silk/NSQ_del_dec.su ./Example/User/CM7/engine/opus/silk/PLC.cyclo ./Example/User/CM7/engine/opus/silk/PLC.d ./Example/User/CM7/engine/opus/silk/PLC.o ./Example/User/CM7/engine/opus/silk/PLC.su ./Example/User/CM7/engine/opus/silk/VAD.cyclo ./Example/User/CM7/engine/opus/silk/VAD.d ./Example/User/CM7/engine/opus/silk/VAD.o ./Example/User/CM7/engine/opus/silk/VAD.su ./Example/User/CM7/engine/opus/silk/VQ_WMat_EC.cyclo ./Example/User/CM7/engine/opus/silk/VQ_WMat_EC.d ./Example/User/CM7/engine/opus/silk/VQ_WMat_EC.o ./Example/User/CM7/engine/opus/silk/VQ_WMat_EC.su ./Example/User/CM7/engine/opus/silk/ana_filt_bank_1.cyclo ./Example/User/CM7/engine/opus/silk/ana_filt_bank_1.d ./Example/User/CM7/engine/opus/silk/ana_filt_bank_1.o ./Example/User/CM7/engine/opus/silk/ana_filt_bank_1.su ./Example/User/CM7/engine/opus/silk/biquad_alt.cyclo ./Example/User/CM7/engine/opus/silk/biquad_alt.d ./Example/User/CM7/engine/opus/silk/biquad_alt.o ./Example/User/CM7/engine/opus/silk/biquad_alt.su ./Example/User/CM7/engine/opus/silk/bwexpander.cyclo ./Example/User/CM7/engine/opus/silk/bwexpander.d ./Example/User/CM7/engine/opus/silk/bwexpander.o ./Example/User/CM7/engine/opus/silk/bwexpander.su ./Example/User/CM7/engine/opus/silk/bwexpander_32.cyclo ./Example/User/CM7/engine/opus/silk/bwexpander_32.d ./Example/User/CM7/engine/opus/silk/bwexpander_32.o ./Example/User/CM7/engine/opus/silk/bwexpander_32.su ./Example/User/CM7/engine/opus/silk/check_control_input.cyclo ./Example/User/CM7/engine/opus/silk/check_control_input.d ./Example/User/CM7/engine/opus/silk/check_control_input.o ./Example/User/CM7/engine/opus/silk/check_control_input.su ./Example/User/CM7/engine/opus/silk/code_signs.cyclo ./Example/User/CM7/engine/opus/silk/code_signs.d ./Example/User/CM7/engine/opus/silk/code_signs.o ./Example/User/CM7/engine/opus/silk/code_signs.su ./Example/User/CM7/engine/opus/silk/control_SNR.cyclo ./Example/User/CM7/engine/opus/silk/control_SNR.d ./Example/User/CM7/engine/opus/silk/control_SNR.o ./Example/User/CM7/engine/opus/silk/control_SNR.su ./Example/User/CM7/engine/opus/silk/control_audio_bandwidth.cyclo ./Example/User/CM7/engine/opus/silk/control_audio_bandwidth.d ./Example/User/CM7/engine/opus/silk/control_audio_bandwidth.o ./Example/User/CM7/engine/opus/silk/control_audio_bandwidth.su ./Example/User/CM7/engine/opus/silk/control_codec.cyclo ./Example/User/CM7/engine/opus/silk/control_codec.d ./Example/User/CM7/engine/opus/silk/control_codec.o
	-$(RM) ./Example/User/CM7/engine/opus/silk/control_codec.su ./Example/User/CM7/engine/opus/silk/debug.cyclo ./Example/User/CM7/engine/opus/silk/debug.d ./Example/User/CM7/engine/opus/silk/debug.o ./Example/User/CM7/engine/opus/silk/debug.su ./Example/User/CM7/engine/opus/silk/dec_API.cyclo ./Example/User/CM7/engine/opus/silk/dec_API.d ./Example/User/CM7/engine/opus/silk/dec_API.o ./Example/User/CM7/engine/opus/silk/dec_API.su ./Example/User/CM7/engine/opus/silk/decode_core.cyclo ./Example/User/CM7/engine/opus/silk/decode_core.d ./Example/User/CM7/engine/opus/silk/decode_core.o ./Example/User/CM7/engine/opus/silk/decode_core.su ./Example/User/CM7/engine/opus/silk/decode_frame.cyclo ./Example/User/CM7/engine/opus/silk/decode_frame.d ./Example/User/CM7/engine/opus/silk/decode_frame.o ./Example/User/CM7/engine/opus/silk/decode_frame.su ./Example/User/CM7/engine/opus/silk/decode_indices.cyclo ./Example/User/CM7/engine/opus/silk/decode_indices.d ./Example/User/CM7/engine/opus/silk/decode_indices.o ./Example/User/CM7/engine/opus/silk/decode_indices.su ./Example/User/CM7/engine/opus/silk/decode_parameters.cyclo ./Example/User/CM7/engine/opus/silk/decode_parameters.d ./Example/User/CM7/engine/opus/silk/decode_parameters.o ./Example/User/CM7/engine/opus/silk/decode_parameters.su ./Example/User/CM7/engine/opus/silk/decode_pitch.cyclo ./Example/User/CM7/engine/opus/silk/decode_pitch.d ./Example/User/CM7/engine/opus/silk/decode_pitch.o ./Example/User/CM7/engine/opus/silk/decode_pitch.su ./Example/User/CM7/engine/opus/silk/decode_pulses.cyclo ./Example/User/CM7/engine/opus/silk/decode_pulses.d ./Example/User/CM7/engine/opus/silk/decode_pulses.o ./Example/User/CM7/engine/opus/silk/decode_pulses.su ./Example/User/CM7/engine/opus/silk/decoder_set_fs.cyclo ./Example/User/CM7/engine/opus/silk/decoder_set_fs.d ./Example/User/CM7/engine/opus/silk/decoder_set_fs.o ./Example/User/CM7/engine/opus/silk/decoder_set_fs.su ./Example/User/CM7/engine/opus/silk/enc_API.cyclo ./Example/User/CM7/engine/opus/silk/enc_API.d ./Example/User/CM7/engine/opus/silk/enc_API.o ./Example/User/CM7/engine/opus/silk/enc_API.su ./Example/User/CM7/engine/opus/silk/encode_indices.cyclo ./Example/User/CM7/engine/opus/silk/encode_indices.d ./Example/User/CM7/engine/opus/silk/encode_indices.o ./Example/User/CM7/engine/opus/silk/encode_indices.su ./Example/User/CM7/engine/opus/silk/encode_pulses.cyclo ./Example/User/CM7/engine/opus/silk/encode_pulses.d ./Example/User/CM7/engine/opus/silk/encode_pulses.o ./Example/User/CM7/engine/opus/silk/encode_pulses.su ./Example/User/CM7/engine/opus/silk/gain_quant.cyclo ./Example/User/CM7/engine/opus/silk/gain_quant.d ./Example/User/CM7/engine/opus/silk/gain_quant.o ./Example/User/CM7/engine/opus/silk/gain_quant.su ./Example/User/CM7/engine/opus/silk/init_decoder.cyclo ./Example/User/CM7/engine/opus/silk/init_decoder.d ./Example/User/CM7/engine/opus/silk/init_decoder.o ./Example/User/CM7/engine/opus/silk/init_decoder.su ./Example/User/CM7/engine/opus/silk/init_encoder.cyclo ./Example/User/CM7/engine/opus/silk/init_encoder.d ./Example/User/CM7/engine/opus/silk/init_encoder.o ./Example/User/CM7/engine/opus/silk/init_encoder.su ./Example/User/CM7/engine/opus/silk/inner_prod_aligned.cyclo ./Example/User/CM7/engine/opus/silk/inner_prod_aligned.d ./Example/User/CM7/engine/opus/silk/inner_prod_aligned.o ./Example/User/CM7/engine/opus/silk/inner_prod_aligned.su ./Example/User/CM7/engine/opus/silk/interpolate.cyclo ./Example/User/CM7/engine/opus/silk/interpolate.d ./Example/User/CM7/engine/opus/silk/interpolate.o ./Example/User/CM7/engine/opus/silk/interpolate.su ./Example/User/CM7/engine/opus/silk/lin2log.cyclo ./Example/User/CM7/engine/opus/silk/lin2log.d ./Example/User/CM7/engine/opus/silk/lin2log.o ./Example/User/CM7/engine/opus/silk/lin2log.su ./Example/User/CM7/engine/opus/silk/log2lin.cyclo ./Example/User/CM7/engine/opus/silk/log2lin.d ./Example/User/CM7/engine/opus/silk/log2lin.o ./Example/User/CM7/engine/opus/silk/log2lin.su ./Example/User/CM7/engine/opus/silk/pitch_est_tables.cyclo ./Example/User/CM7/engine/opus/silk/pitch_est_tables.d ./Example/User/CM7/engine/opus/silk/pitch_est_tables.o ./Example/User/CM7/engine/opus/silk/pitch_est_tables.su ./Example/User/CM7/engine/opus/silk/process_NLSFs.cyclo ./Example/User/CM7/engine/opus/silk/process_NLSFs.d ./Example/User/CM7/engine/opus/silk/process_NLSFs.o ./Example/User/CM7/engine/opus/silk/process_NLSFs.su ./Example/User/CM7/engine/opus/silk/quant_LTP_gains.cyclo ./Example/User/CM7/engine/opus/silk/quant_LTP_gains.d ./Example/User/CM7/engine/opus/silk/quant_LTP_gains.o ./Example/User/CM7/engine/opus/silk/quant_LTP_gains.su ./Example/User/CM7/engine/opus/silk/resampler.cyclo ./Example/User/CM7/engine/opus/silk/resampler.d ./Example/User/CM7/engine/opus/silk/resampler.o ./Example/User/CM7/engine/opus/silk/resampler.su ./Example/User/CM7/engine/opus/silk/resampler_down2.cyclo ./Example/User/CM7/engine/opus/silk/resampler_down2.d ./Example/User/CM7/engine/opus/silk/resampler_down2.o ./Example/User/CM7/engine/opus/silk/resampler_down2.su ./Example/User/CM7/engine/opus/silk/resampler_down2_3.cyclo ./Example/User/CM7/engine/opus/silk/resampler_down2_3.d ./Example/User/CM7/engine/opus/silk/resampler_down2_3.o ./Example/User/CM7/engine/opus/silk/resampler_down2_3.su ./Example/User/CM7/engine/opus/silk/resampler_private_AR2.cyclo ./Example/User/CM7/engine/opus/silk/resampler_private_AR2.d ./Example/User/CM7/engine/opus/silk/resampler_private_AR2.o ./Example/User/CM7/engine/opus/silk/resampler_private_AR2.su ./Example/User/CM7/engine/opus/silk/resampler_private_IIR_FIR.cyclo ./Example/User/CM7/engine/opus/silk/resampler_private_IIR_FIR.d ./Example/User/CM7/engine/opus/silk/resampler_private_IIR_FIR.o ./Example/User/CM7/engine/opus/silk/resampler_private_IIR_FIR.su ./Example/User/CM7/engine/opus/silk/resampler_private_down_FIR.cyclo ./Example/User/CM7/engine/opus/silk/resampler_private_down_FIR.d ./Example/User/CM7/engine/opus/silk/resampler_private_down_FIR.o
	-$(RM) ./Example/User/CM7/engine/opus/silk/resampler_private_down_FIR.su ./Example/User/CM7/engine/opus/silk/resampler_private_up2_HQ.cyclo ./Example/User/CM7/engine/opus/silk/resampler_private_up2_HQ.d ./Example/User/CM7/engine/opus/silk/resampler_private_up2_HQ.o ./Example/User/CM7/engine/opus/silk/resampler_private_up2_HQ.su ./Example/User/CM7/engine/opus/silk/resampler_rom.cyclo ./Example/User/CM7/engine/opus/silk/resampler_rom.d ./Example/User/CM7/engine/opus/silk/resampler_rom.o ./Example/User/CM7/engine/opus/silk/resampler_rom.su ./Example/User/CM7/engine/opus/silk/shell_coder.cyclo ./Example/User/CM7/engine/opus/silk/shell_coder.d ./Example/User/CM7/engine/opus/silk/shell_coder.o ./Example/User/CM7/engine/opus/silk/shell_coder.su ./Example/User/CM7/engine/opus/silk/sigm_Q15.cyclo ./Example/User/CM7/engine/opus/silk/sigm_Q15.d ./Example/User/CM7/engine/opus/silk/sigm_Q15.o ./Example/User/CM7/engine/opus/silk/sigm_Q15.su ./Example/User/CM7/engine/opus/silk/sort.cyclo ./Example/User/CM7/engine/opus/silk/sort.d ./Example/User/CM7/engine/opus/silk/sort.o ./Example/User/CM7/engine/opus/silk/sort.su ./Example/User/CM7/engine/opus/silk/stereo_LR_to_MS.cyclo ./Example/User/CM7/engine/opus/silk/stereo_LR_to_MS.d ./Example/User/CM7/engine/opus/silk/stereo_LR_to_MS.o ./Example/User/CM7/engine/opus/silk/stereo_LR_to_MS.su ./Example/User/CM7/engine/opus/silk/stereo_MS_to_LR.cyclo ./Example/User/CM7/engine/opus/silk/stereo_MS_to_LR.d ./Example/User/CM7/engine/opus/silk/stereo_MS_to_LR.o ./Example/User/CM7/engine/opus/silk/stereo_MS_to_LR.su ./Example/User/CM7/engine/opus/silk/stereo_decode_pred.cyclo ./Example/User/CM7/engine/opus/silk/stereo_decode_pred.d ./Example/User/CM7/engine/opus/silk/stereo_decode_pred.o ./Example/User/CM7/engine/opus/silk/stereo_decode_pred.su ./Example/User/CM7/engine/opus/silk/stereo_encode_pred.cyclo ./Example/User/CM7/engine/opus/silk/stereo_encode_pred.d ./Example/User/CM7/engine/opus/silk/stereo_encode_pred.o ./Example/User/CM7/engine/opus/silk/stereo_encode_pred.su ./Example/User/CM7/engine/opus/silk/stereo_find_predictor.cyclo ./Example/User/CM7/engine/opus/silk/stereo_find_predictor.d ./Example/User/CM7/engine/opus/silk/stereo_find_predictor.o ./Example/User/CM7/engine/opus/silk/stereo_find_predictor.su ./Example/User/CM7/engine/opus/silk/stereo_quant_pred.cyclo ./Example/User/CM7/engine/opus/silk/stereo_quant_pred.d ./Example/User/CM7/engine/opus/silk/stereo_quant_pred.o ./Example/User/CM7/engine/opus/silk/stereo_quant_pred.su ./Example/User/CM7/engine/opus/silk/sum_sqr_shift.cyclo ./Example/User/CM7/engine/opus/silk/sum_sqr_shift.d ./Example/User/CM7/engine/opus/silk/sum_sqr_shift.o ./Example/User/CM7/engine/opus/silk/sum_sqr_shift.su ./Example/User/CM7/engine/opus/silk/table_LSF_cos.cyclo ./Example/User/CM7/engine/opus/silk/table_LSF_cos.d ./Example/User/CM7/engine/opus/silk/table_LSF_cos.o ./Example/User/CM7/engine/opus/silk/table_LSF_cos.su ./Example/User/CM7/engine/opus/silk/tables_LTP.cyclo ./Example/User/CM7/engine/opus/silk/tables_LTP.d ./Example/User/CM7/engine/opus/silk/tables_LTP.o ./Example/User/CM7/engine/opus/silk/tables_LTP.su ./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_NB_MB.cyclo ./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_NB_MB.d ./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_NB_MB.o ./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_NB_MB.su ./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_WB.cyclo ./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_WB.d ./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_WB.o ./Example/User/CM7/engine/opus/silk/tables_NLSF_CB_WB.su ./Example/User/CM7/engine/opus/silk/tables_gain.cyclo ./Example/User/CM7/engine/opus/silk/tables_gain.d ./Example/User/CM7/engine/opus/silk/tables_gain.o ./Example/User/CM7/engine/opus/silk/tables_gain.su ./Example/User/CM7/engine/opus/silk/tables_other.cyclo ./Example/User/CM7/engine/opus/silk/tables_other.d ./Example/User/CM7/engine/opus/silk/tables_other.o ./Example/User/CM7/engine/opus/silk/tables_other.su ./Example/User/CM7/engine/opus/silk/tables_pitch_lag.cyclo ./Example/User/CM7/engine/opus/silk/tables_pitch_lag.d ./Example/User/CM7/engine/opus/silk/tables_pitch_lag.o ./Example/User/CM7/engine/opus/silk/tables_pitch_lag.su ./Example/User/CM7/engine/opus/silk/tables_pulses_per_block.cyclo ./Example/User/CM7/engine/opus/silk/tables_pulses_per_block.d ./Example/User/CM7/engine/opus/silk/tables_pulses_per_block.o ./Example/User/CM7/engine/opus/silk/tables_pulses_per_block.su

.PHONY: clean-Example-2f-User-2f-CM7-2f-engine-2f-opus-2f-silk

