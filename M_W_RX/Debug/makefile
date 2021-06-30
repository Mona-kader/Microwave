################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/timer/subdir.mk
-include MCAL/UART/subdir.mk
-include LIB/string/subdir.mk
-include HAL/LCD/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
M_W_RX.lss \

FLASH_IMAGE += \
M_W_RX.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: M_W_RX.elf secondary-outputs

# Tool invocations
M_W_RX.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,M_W_RX.map -mmcu=atmega16 -o "M_W_RX.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

M_W_RX.lss: M_W_RX.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S M_W_RX.elf  >"M_W_RX.lss"
	@echo 'Finished building: $@'
	@echo ' '

M_W_RX.hex: M_W_RX.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex M_W_RX.elf  "M_W_RX.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: M_W_RX.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 M_W_RX.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: M_W_RX.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm16 -cusbasp -Uflash:w:M_W_RX.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) M_W_RX.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
