CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g -MMD -MP
SFML_DIR = /home/sgo/SFML-3.0.2
# SFML_DIR = /home/bomsai/SFML-3.0.2
CXXFLAGS += -I$(SFML_DIR)/include
LDFLAGS = -L$(SFML_DIR)/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o
all: main

main: $(OBJS)
	$(CXX) $(OBJS) -o main $(LDFLAGS) $(LIBS)

main.o: main.cpp enums.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o *.d main

.PHONY: all clean
