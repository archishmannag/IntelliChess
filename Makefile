# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c++17

# Libraries
LIBS = -lncursesw

# Source files
SRCS = main.cpp ChessGame.cpp MoveHighlighter.cpp TerminalSizeWatcher.cpp

# Source directories
VPATH = src

# Object directory
ODIR = build

# Executable directory
EDIR = bin

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
TARGET = chess.out

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: $(VPATH)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $(ODIR)/$@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(ODIR)/* -o $(EDIR)/$@ $(LIBS)

# Clean up object files and executable
clean:
	rm -f $(ODIR)/* $(EDIR)/$(TARGET)
