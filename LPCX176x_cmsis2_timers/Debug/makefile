################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LPCX176x_cmsis2_timers.axf

# Tool invocations
LPCX176x_cmsis2_timers.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\LPC1769\LPC1769\CMSISv2p00_LPC17xx\Debug" -Xlinker -Map=LPCX176x_cmsis2_timers.map -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "LPCXpresso176x_timers_Debug.ld" -o "LPCX176x_cmsis2_timers.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) LPCX176x_cmsis2_timers.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size LPCX176x_cmsis2_timers.axf; # arm-none-eabi-objcopy -O binary LPCX176x_cmsis2_timers.axf LPCX176x_cmsis2_timers.bin ; checksum -p LPC1768 -d LPCX176x_cmsis2_timers.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
