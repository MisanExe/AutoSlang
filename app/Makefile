PROJECT = blink-led
BUILD_DIR ?= bin
FLASH_ADDR ?= 0x8000000

#SHARED_DIR = ../my-common-code
CFILES = src/main.c
CFILES += src/uart.c
CFILES += src/buffer.c
CFILES += src/rtc.c
CFILES += src/logger.c
CFILES += src/spi.c

INCLUDE_DIR = inc

#AFILES += api-asm.S

# TODO - you will need to edit these two lines!
DEVICE=stm32f103C6T6A
OOCD_FILE = board/stm32f103c8_blue_pill.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))  #includes from shared directory
INCLUDES += $(patsubst %,-I%, . $(INCLUDE_DIR)) #includes from project directory
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk

flash:$(PROJECT).bin
	st-flash write $(PROJECT).bin $(FLASH_ADDR)
	
debug:$(PROJECT).bin $(PROJECT).elf
	gdb-multiarch $(PROJECT).elf

clean += \
	rm -f $(BUILD_DIR)/*.o \
	rm -f $(BUILD_DIR)/src/*.o \
	rm -f $(BUILD_DIR)/src/*.d \
	rm -f $(PROJECT).elf \
	rm -f $(PROJECT).bin 

help:
	@echo "Makefile targets:"
	@echo "   	- Builds the main project executable."
	@echo "clean 	- Removes all build artifacts and generated files"
	@echo "flash 	- flash the project executable "