# Makefile for SDL3 project on macOS with clang

# Compiler
CC = clang

# Executable name
TARGET = main

# Source files
SRC = main.c

# SDL3 paths (Homebrew default)
SDL_INC = /opt/homebrew/opt/sdl3/include
SDL_LIB = /opt/homebrew/opt/sdl3/lib

# Compiler flags
CFLAGS = -I$(SDL_INC) -Wall
LDFLAGS = -L$(SDL_LIB) -lSDL3

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)
