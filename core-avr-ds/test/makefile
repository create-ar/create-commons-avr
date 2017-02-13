override CC=g++
override SOURCES=$(wildcard *.cpp)
override OUT_DIR=build
override OBJ_DIR=$(OUT_DIR)/obj
override EXE_NAME=$(OUT_DIR)/Test.exe

override OBJS=$(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.cpp=.o)))

all: $(OBJS)
	$(CC) -o $(EXE_NAME) $(OBJS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(TESTINC) -c $< -o $(OBJ_DIR)/$(@F)

clean:
	rm -Rf $(OUT_DIR)