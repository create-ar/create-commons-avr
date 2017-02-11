ARDUINODIR=C:\Program\ Files\ \(x86\)\Arduino
CC=$(ARDUINODIR)\hardware\tools\avr\bin\avr-g++.exe
ARCHIVER=$(ARDUINODIR)\hardware\tools\avr\bin\avr-ar.exe
TARGETDIR=../libs

CPUNAME=atmega328p
CPUCLOCK=16000000L
CFLAGS=-c -g -Os -Wall -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -DARDUINO=100 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR -mmcu=$(CPUNAME) -DF_CPU=$(CPUCLOCK)
COREINC=-I$(ARDUINODIR)\hardware\arduino\avr\cores\arduino
INC=-I$(ARDUINODIR)\hardware\arduino\avr\libraries\SoftwareSerial
LIBNAME=core-avr-data

SOURCES=\
	EEPROMStream.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TEMP_D=$(SOURCES:.cpp=.d)

all:
	$(CC) $(CFLAGS) $(COREINC) $(INC) $(SOURCES)
	$(ARCHIVER) rcs $(TARGETDIR)/lib$(LIBNAME).a $(OBJECTS)
	rm $(OBJECTS)
	rm $(TEMP_D)