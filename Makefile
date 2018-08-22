TARGET=garbage_collector_cpp
TARGET_BINARY=$(TARGET).bin
CC=clang++
CPP_FLAGS=-W -Wall -g -std=c++14 -stdlib=libc++
SRC=$(wildcard *.cpp)
all: $(TARGET)
$(TARGET):
	$(CC) $(CPP_FLAGS) $(SRC) -o $(TARGET_BINARY)
clean:
	rm -f $(TARGET_BINARY)
