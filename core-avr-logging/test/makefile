OUT_DIR=build
OBJ_DIR=$(OUT_DIR)/obj
EXE_NAME=$(OUT_DIR)/Test.exe

CC=g++
CFLAGS=-g -Os -Wall -Werror -std=gnu++11
INC=-IC:\Projects\ThirdParty\Catch\single_include\
	-I../../core-avr-ds/src

TEST_SOURCES=\
	Main_core-avr-logging.cpp
INC_SOURCES=\
	../src/Log.cpp\
	../src/Logger.cpp

OBJS=build/obj/Main_core-avr-logging.o build/obj/Log.o build/obj/Logger.o

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

build/obj/Log.o: ../src/Log.cpp
	$(CC) $(CFLAGS) $(INC) -I../src -c ../src/Log.cpp -o $(OBJ_DIR)/Log.o

build/obj/Logger.o: ../src/Logger.cpp
	$(CC) $(CFLAGS) $(INC) -I../src -c ../src/Logger.cpp -o $(OBJ_DIR)/Logger.o

build/obj/Main_core-avr-logging.o: Main_core-avr-logging.cpp
	$(CC) $(CFLAGS) $(INC) -I../src -c Main_core-avr-logging.cpp -o $(OBJ_DIR)/Main_core-avr-logging.o

clean:
	rm -Rf $(OUT_DIR)