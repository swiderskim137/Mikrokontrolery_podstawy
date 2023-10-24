################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
klaskacz.lss \

FLASH_IMAGE += \
klaskacz.hex \

EEPROM_IMAGE += \
klaskacz.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: klaskacz.elf secondary-outputs

# Tool invocations
klaskacz.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,klaskacz.map -mmcu=attiny45 -o "klaskacz.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

klaskacz.lss: klaskacz.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S klaskacz.elf  >"klaskacz.lss"
	@echo 'Finished building: $@'
	@echo ' '

klaskacz.hex: klaskacz.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex klaskacz.elf  "klaskacz.hex"
	@echo 'Finished building: $@'
	@echo ' '

klaskacz.eep: klaskacz.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex klaskacz.elf  "klaskacz.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: klaskacz.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny45 klaskacz.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) klaskacz.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
