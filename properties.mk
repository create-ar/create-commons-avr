# base dir for everything
BASE_DIR=/cygdrive/c/Projects

# base directory for all core projects
BASECORE_DIR=$(BASE_DIR)/openfarm-core-avr

# third part directory
THIRDPARTY_DIR=$(BASE_DIR)/Libraries

# base arduino directory
ARDUINO_DIR=$(BASE_DIR)/ThirdParty/Arduino

# include for Catch.hpp
TEST_INCLUDES=-I$(BASE_DIR)/ThirdParty/Catch/single_include

# arduino variant
VARIANT=standard

# The microcontroler used.
CPUNAME=atmega328p

# Clock speed of the board.
CPUCLOCK=16000000L

# Compiler flags for all architectures
COMMON_CFLAGS=-g -Os -Wall -Werror -std=gnu++11

# Lib folder
LIB_DIR=$(BASECORE_DIR)/libs

# AVR properties
AVR_INCLUDES=-I$(ARDUINO_DIR)/hardware/arduino/avr/cores/arduino -I$(ARDUINO_DIR)/hardware/arduino/avr/variants/$(VARIANT) -I$(ARDUINO_DIR)/hardware/tools/avr/avr/include
AVR_CFLAGS=$(COMMON_CFLAGS) -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -DARDUINO=100 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR -mmcu=$(CPUNAME) -DF_CPU=$(CPUCLOCK)
AVR_ARCHIVER=$(ARDUINODIR)/hardware/tools/avr/bin/avr-ar.exe
AVR_CC=$(ARDUINO_DIR)/hardware/tools/avr/bin/avr-g++.exe

# Local architecture properties
x86_INCLUDES=$(AVR_INCLUDES)
x86_CFLAGS=$(COMMON_CFLAGS)
x86_ARCHIVER=ar
x86_CC=g++
