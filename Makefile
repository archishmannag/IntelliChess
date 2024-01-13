# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c++11

# Libraries
LIBS = -lncurses -lncursesw

# Source files
SRCS = main.cpp ChessGame.cpp MoveHighlighter.cpp TerminalSizeWatcher.cpp

# Source directories
VPATH = src

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
TARGET = chess.out

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: $(VPATH)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
