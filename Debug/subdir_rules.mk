################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include" --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/Tic - Tac- Toe" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/HW-3/HW02-Dist" --include_path="C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ps2.obj: C:/Users/13478/Desktop/ece353/Free-RTOS/HW-3/HW02-Dist/ps2.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include" --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/Tic - Tac- Toe" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/HW-3/HW02-Dist" --include_path="C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="ps2.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tic_tac_toe.obj: C:/Users/13478/Desktop/ece353/Free-RTOS/HW-3/HW02-Dist/tic_tac_toe.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include" --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/Tic - Tac- Toe" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/HW-3/HW02-Dist" --include_path="C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="tic_tac_toe.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tic_tac_toe_images.obj: C:/Users/13478/Desktop/ece353/Free-RTOS/HW-3/HW02-Dist/tic_tac_toe_images.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include" --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/Tic - Tac- Toe" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/HW-3/HW02-Dist" --include_path="C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="tic_tac_toe_images.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

timer32.obj: C:/Users/13478/Desktop/ece353/Free-RTOS/HW-3/HW02-Dist/timer32.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include" --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/Tic - Tac- Toe" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/HW-3/HW02-Dist" --include_path="C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="timer32.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


