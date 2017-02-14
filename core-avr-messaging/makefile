###############################################################################
# Library includes. Eg -
# -I$(ARDUINODIR)\hardware\arduino\avr\libraries\SoftwareSerial
INC=-I$(ARDUINODIR)\hardware\arduino\avr\libraries\SoftwareSerial
###############################################################################

###############################################################################
# Name of the library. This will automatically be prefixed by 'lib'. Eg -
# core-avr-data
LIBNAME=core-avr-messaging
###############################################################################

###############################################################################
# All source files. Eg -
# Foo.cpp Bar.cpp
SOURCES=\
	Message.cpp\
	Messaging.cpp\
	SoftwareSerialSession.cpp\
	StreamReader.cpp\
	StreamWriter.cpp
###############################################################################

###############################################################################
# Directory to compile to.
TARGETDIR=../libs
###############################################################################

# Compiler flags: don't touch unless you know what you're doing.
CFLAGS=-c -g -Os -Wall -Werror -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -DARDUINO=100 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR -mmcu=$(CPUNAME) -DF_CPU=$(CPUCLOCK)

# Temporary build files.
OBJS=$(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
LIBPATH=$(TARGETDIR)/lib$(LIBNAME).a

all: $(OBJS)
	$(ARCHIVER) rcs $(LIBPATH) $(OBJS)
	
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) $(COREINC) $(VARIANTINC) $(ARDUINOINC) -c $< -o $(OBJ_DIR)/$(@F)

clean:
	rm -Rf $(OUT_DIR)
	rm -f $(LIBPATH)