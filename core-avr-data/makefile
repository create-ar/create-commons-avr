###############################################################################
# Library includes. Eg -
# -I$(ARDUINODIR)\hardware\arduino\avr\libraries\SoftwareSerial
INC=
###############################################################################

###############################################################################
# Name of the library. This will automatically be prefixed by 'lib'. Eg -
# core-avr-data
LIBNAME=core-avr-data
###############################################################################

###############################################################################
# All source files. Eg -
# Foo.cpp Bar.cpp
SOURCES=\
	EEPROMStream.cpp\
	File.cpp
###############################################################################

###############################################################################
# Directory to compile to.
TARGETDIR=../libs
###############################################################################

# Compiler flags: don't touch unless you know what you're doing.
CFLAGS=-c -g -Os -Wall -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -DARDUINO=100 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR -mmcu=$(CPUNAME) -DF_CPU=$(CPUCLOCK)

# Temporary build files.
OBJECTS=$(SOURCES:.cpp=.o)
TEMP_D=$(SOURCES:.cpp=.d)

all:
	$(CC) $(CFLAGS) $(COREINC) $(INC) $(SOURCES)
	$(ARCHIVER) rcs $(TARGETDIR)/lib$(LIBNAME).a $(OBJECTS)
	rm $(OBJECTS)
	rm $(TEMP_D)