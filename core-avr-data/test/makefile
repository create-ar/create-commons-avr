OUT_DIR=build
OBJ_DIR=$(OUT_DIR)/obj
EXE_NAME=$(OUT_DIR)/Test.exe

CC=g++
CFLAGS=-g -Os -Wall -Werror -std=gnu++11
INC=\
	-I$(BASECOREDIR)/core-avr-ds/src\
	-I$(BASECOREDIR)/core-avr-logging/src\
	-I$(BASECOREDIR)/common
TEST_INC=-IC:\Projects\ThirdParty\Catch\single_include

TEST_SOURCES=\
	Main_core-avr-data.cpp\
	File_Tests.cpp\
	MemoryStream_Tests.cpp
INC_SOURCES=\
	../src/File.cpp\
	../src/FileManager.cpp\
	../src/MemoryStreamer.cpp

OBJS=\
	$(OBJ_DIR)/Main_core-avr-data.o\
	$(OBJ_DIR)/File_Tests.o\
	$(OBJ_DIR)/MemoryStream_Tests.o\
	$(OBJ_DIR)/File.o\
	$(OBJ_DIR)/FileManager.o\
	$(OBJ_DIR)/MemoryStreamer.o

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