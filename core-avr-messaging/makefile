###############################################################################
# Library includes.
# 
# Eg:
# 
# -I$(ARDUINODIR)\hardware\arduino\avr\libraries\SoftwareSerial
#
INC=\
	-I$(ARDUINODIR)\hardware\arduino\avr\libraries\SoftwareSerial\
	-I$(BASECOREDIR)\core-avr-ds\src\
	-I$(BASECOREDIR)\common
###############################################################################

###############################################################################
# Name of the library. This will automatically be prefixed by 'lib'.
# 
# Eg:
# 
# core-avr-data
# 
LIBNAME=core-avr-messaging
###############################################################################

###############################################################################
# All source files.
# 
# Eg:
# 
# Foo.cpp Bar.cpp
# 
SOURCES=\
	src/Message.cpp\
	src/Messaging.cpp\
	src/SoftwareSerialSession.cpp\
	src/StreamReader.cpp\
	src/StreamWriter.cpp
###############################################################################

###############################################################################
# Directory to compile to.
TARGETDIR=../libs
###############################################################################

# Temporary build files.
OBJS=$(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
LIBPATH=$(TARGETDIR)/lib$(LIBNAME).a

all: $(OBJS)
	$(ARCHIVER) rcs $(LIBPATH) $(OBJS)
	
$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)

	# build for arduino architecture
	$(CC) $(CFLAGS) $(INC) $(COREINC) $(VARIANTINC) $(ARDUINOINC) -c $< -o $(OBJ_DIR)/$(@F)