# Compiler variables
CC= g++ 
CFLAGS= -std=c++17

# Libraries and includes
LINKDIR= -L../dragonfly/lib # path to dragonfly library
INCDIR= -I../dragonfly/include # path to dragonfly includes
SFML_VERSION= 3.0.0

ENG= dragonfly
LOCALSFML= /opt/homebrew/Cellar/sfml/$(SFML_VERSION)
LINKLIB= -l$(ENG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
LINKDIR:= $(LINKDIR) -L $(LOCALSFML)/lib
INCDIR:= $(INCDIR) -I$(LOCALSFML)/include

######

GAMESRC= \
	SceneController.cpp \
	GameController.cpp \
	Crate.cpp

GAME= game.cpp
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)

.PHONY: all clean

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) $(CFLAGS) -c $< -o $@ $(INCDIR)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~
# DO NOT DELETE
