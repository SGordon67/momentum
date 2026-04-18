CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g -MMD -MP
# SFML_DIR = /home/sgo/SFML-3.0.2
SFML_DIR = /home/bomsai/SFML-3.0.2
CXXFLAGS += -I$(SFML_DIR)/include
LDFLAGS = -L$(SFML_DIR)/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o InputSystem.o MainMenuState.o MainMenu.o SettingsState.o SettingsMenu.o PlayingState.o MenuLabel.o MenuButton.o Dropdown.o VisibleObj.o PhysicalObj.o Player.o
all: main

main: $(OBJS)
	$(CXX) $(OBJS) -o main $(LDFLAGS) $(LIBS)

main.o: main.cpp InputSystem.h MainMenu.h MenuLabel.h MenuButton.h VisibleObj.h PhysicalObj.h Player.h enums.h
	$(CXX) $(CXXFLAGS) -c main.cpp

InputSystem.o: InputSystem.cpp InputSystem.h enums.h
	$(CXX) $(CXXFLAGS) -c InputSystem.cpp

MainMenuState.o: MainMenuState.cpp MainMenuState.h PlayingState.h GameState.h
	$(CXX) $(CXXFLAGS) -c MainMenuState.cpp

MainMenu.o: MainMenu.cpp MainMenu.h InputSystem.h
	$(CXX) $(CXXFLAGS) -c MainMenu.cpp

SettingsState.o: SettingsState.cpp SettingsState.h SettingsMenu.h GameState.h
	$(CXX) $(CXXFLAGS) -c SettingsState.cpp

SettingsMenu.o: SettingsMenu.cpp SettingsMenu.h InputSystem.h
	$(CXX) $(CXXFLAGS) -c SettingsMenu.cpp

PlayingState.o: PlayingState.cpp PlayingState.h MainMenuState.h GameState.h
	$(CXX) $(CXXFLAGS) -c PlayingState.cpp

MenuLabel.o: MenuLabel.cpp MenuLabel.h MainMenu.h
	$(CXX) $(CXXFLAGS) -c MenuLabel.cpp

MenuButton.o: MenuButton.cpp MenuButton.h MainMenu.h
	$(CXX) $(CXXFLAGS) -c MenuButton.cpp

Dropdown.o: Dropdown.cpp Dropdown.h MainMenu.h
	$(CXX) $(CXXFLAGS) -c Dropdown.cpp

VisibleObj.o: VisibleObj.cpp VisibleObj.h enums.h
	$(CXX) $(CXXFLAGS) -c VisibleObj.cpp

PhysicalObj.o: PhysicalObj.cpp PhysicalObj.h VisibleObj.h enums.h
	$(CXX) $(CXXFLAGS) -c PhysicalObj.cpp

Player.o: Player.cpp Player.h PhysicalObj.h enums.h
	$(CXX) $(CXXFLAGS) -c Player.cpp

clean:
	rm -f *.o *.d main

.PHONY: all clean
