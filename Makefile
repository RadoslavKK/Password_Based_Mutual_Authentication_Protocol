CXX = g++
CXXFLAGS = -Wall -Iinclude
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))
TARGET = bin/DeviceConnector++

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CXX) $(OBJ) -o $@

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET) keys/base64Key.txt

clean:
	rm -rf build bin/*
