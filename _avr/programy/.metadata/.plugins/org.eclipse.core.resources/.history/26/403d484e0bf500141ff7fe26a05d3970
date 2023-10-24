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
kontroler_oœwietlenia.lss \

FLASH_IMAGE += \
kontroler_oœwietlenia.hex \

EEPROM_IMAGE += \
kontroler_oœwietlenia.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: kontroler_oœwietlenia.elf secondary-outputs

# Tool invocations
kontroler_oœwietlenia.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,kontroler_oœwietlenia.map -mmcu=atmega8 -o "kontroler_oœwietlenia.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

kontroler_oœwietlenia.lss: kontroler_oœwietlenia.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S kontroler_oœwietlenia.elf  >"kontroler_oœwietlenia.lss"
	@echo 'Finished building: $@'
	@echo ' '

kontroler_oœwietlenia.hex: kontroler_oœwietlenia.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex kontroler_oœwietlenia.elf  "kontroler_oœwietlenia.hex"
	@echo 'Finished building: $@'
	@echo ' '

kontroler_oœwietlenia.eep: kontroler_oœwietlenia.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex kontroler_oœwietlenia.elf  "kontroler_oœwietlenia.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: kontroler_oœwietlenia.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 kontroler_oœwietlenia.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) kontroler_oœwietlenia.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
