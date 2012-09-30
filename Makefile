# OSRC = $(shell find -name '*.h')
SRCS = $(shell find -name '*.cpp')

CC	= g++

# CFLAGS = -Wall -g 
CFLAGS = -g
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) $(CFLAGS) $(SRCS) -o ActionRPG $(LFLAGS)
