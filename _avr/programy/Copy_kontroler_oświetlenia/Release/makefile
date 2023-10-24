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
Copy_kontroler_oœwietlenia.lss \

FLASH_IMAGE += \
Copy_kontroler_oœwietlenia.hex \

EEPROM_IMAGE += \
Copy_kontroler_oœwietlenia.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Copy_kontroler_oœwietlenia.elf secondary-outputs

# Tool invocations
Copy_kontroler_oœwietlenia.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Copy_kontroler_oœwietlenia.map -mmcu=atmega8 -o "Copy_kontroler_oœwietlenia.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Copy_kontroler_oœwietlenia.lss: Copy_kontroler_oœwietlenia.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Copy_kontroler_oœwietlenia.elf  >"Copy_kontroler_oœwietlenia.lss"
	@echo 'Finished building: $@'
	@echo ' '

Copy_kontroler_oœwietlenia.hex: Copy_kontroler_oœwietlenia.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Copy_kontroler_oœwietlenia.elf  "Copy_kontroler_oœwietlenia.hex"
	@echo 'Finished building: $@'
	@echo ' '

Copy_kontroler_oœwietlenia.eep: Copy_kontroler_oœwietlenia.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Copy_kontroler_oœwietlenia.elf  "Copy_kontroler_oœwietlenia.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Copy_kontroler_oœwietlenia.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 Copy_kontroler_oœwietlenia.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Copy_kontroler_oœwietlenia.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
