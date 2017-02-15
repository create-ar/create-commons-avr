OUT_DIR=build
OBJ_DIR=$(OUT_DIR)/obj
EXE_NAME=$(OUT_DIR)/Test.exe

CC=g++
CFLAGS=-g -Os -Wall -Werror -std=gnu++11
INC=-I../../core-avr-ds/src
TEST_INC=-IC:\Projects\ThirdParty\Catch\single_include

TEST_SOURCES=\
	Main_core-avr-logging.cpp\
	Log_Tests.cpp\
	DefaultFormatter_Tests.cpp
INC_SOURCES=\
	../src/Log.cpp\
	../src/Logger.cpp

OBJS=build/obj/Main_core-avr-logging.o\
	build/obj/Log_Tests.o\
	build/obj/DefaultFormatter_Tests.o\
	build/obj/Log.o\
	build/obj/Logger.o

.PHONY: all clean

all: post-build

pre-build:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)

post-build: main-build
	@echo Complete.

main-build: pre-build
	@$(MAKE) --no-print-directory target

target: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE_NAME) $(OBJS)

VPATH=../src

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) $(TEST_INC) -I../src -c $< -o $(OBJ_DIR)/$(@F)

clean:
	rm -Rf $(OUT_DIR)