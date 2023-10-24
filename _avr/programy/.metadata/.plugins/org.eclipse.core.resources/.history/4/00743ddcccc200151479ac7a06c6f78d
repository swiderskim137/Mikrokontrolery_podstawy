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
Voyager_swiatla.lss \

FLASH_IMAGE += \
Voyager_swiatla.hex \

EEPROM_IMAGE += \
Voyager_swiatla.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Voyager_swiatla.elf secondary-outputs

# Tool invocations
Voyager_swiatla.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Voyager_swiatla.map -mmcu=attiny45 -o "Voyager_swiatla.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Voyager_swiatla.lss: Voyager_swiatla.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Voyager_swiatla.elf  >"Voyager_swiatla.lss"
	@echo 'Finished building: $@'
	@echo ' '

Voyager_swiatla.hex: Voyager_swiatla.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Voyager_swiatla.elf  "Voyager_swiatla.hex"
	@echo 'Finished building: $@'
	@echo ' '

Voyager_swiatla.eep: Voyager_swiatla.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Voyager_swiatla.elf  "Voyager_swiatla.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Voyager_swiatla.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny45 Voyager_swiatla.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Voyager_swiatla.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
