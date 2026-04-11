CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g -MMD -MP
# SFML_DIR = /home/sgo/SFML-3.0.2
SFML_DIR = /home/bomsai/SFML-3.0.2
CXXFLAGS += -I$(SFML_DIR)/include
LDFLAGS = -L$(SFML_DIR)/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o MainMenu.o MenuLabel.o MenuButton.o
all: main

main: $(OBJS)
	$(CXX) $(OBJS) -o main $(LDFLAGS) $(LIBS)

main.o: main.cpp MainMenu.h MenuLabel.h MenuButton.h enums.h
	$(CXX) $(CXXFLAGS) -c main.cpp

MainMenu.o: MainMenu.cpp
	$(CXX) $(CXXFLAGS) -c MainMenu.cpp

MenuLabel.o: MenuLabel.cpp
	$(CXX) $(CXXFLAGS) -c MenuLabel.cpp

MenuButton.o: MenuButton.cpp
	$(CXX) $(CXXFLAGS) -c MenuButton.cpp

clean:
	rm -f *.o *.d main

.PHONY: all clean
