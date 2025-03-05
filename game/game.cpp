// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Game includes.
#include "GameStart.h"

int loadResources();

int main(int argc, char *argv[]) {
    GM.startUp();
    if (loadResources() == -1) {
        LM.writeLog("Error loading resources.");
        return -1;
    }

    //new SceneController();

    new GameStart;

    GM.run();

    GM.shutDown();
    return 0;
}

int loadResources() {
    // If any of the resources fail to load, return -1, otherwise return 0.
    return (RM.loadSprite("sprites/crate-spr.txt", "crate") == 0 &&
        RM.loadSprite("sprites/game-over-spr.txt", "game-over") == 0 &&
        RM.loadSprite("sprites/game-start-spr.txt", "game-start") == 0 &&
        RM.loadSprite("sprites/insert-coin-spr.txt", "insert-coin") == 0 &&
        RM.loadSprite("sprites/tower-base-spr.txt", "tower-base") == 0 &&
        RM.loadSprite("sprites/highest-point-spr.txt", "highest-point") == 0 &&
        RM.loadSprite("sprites/star-spr.txt", "star") == 0 &&
        RM.loadSprite("sprites/planet-spr.txt", "planet") == 0 &&
        RM.loadSprite("sprites/prize-nothing-spr.txt", "prize-nothing") == 0 &&
        RM.loadSprite("sprites/prize-toilet-paper-spr.txt", "prize-toilet-paper") == 0 &&
        RM.loadSprite("sprites/prize-eggs-spr.txt", "prize-eggs") == 0 &&
        RM.loadSprite("sprites/prize-socks-spr.txt", "prize-socks") == 0 &&
        RM.loadSprite("sprites/prize-otter-spr.txt", "prize-otter") == 0 &&
        RM.loadSprite("sprites/prize-crown-spr.txt", "prize-crown") == 0 &&
        RM.loadSprite("sprites/prize-car-spr.txt", "prize-car") == 0 &&
        RM.loadSprite("sprites/prize-liberty-spr.txt", "prize-liberty") == 0 &&
        RM.loadSprite("sprites/prize-cool-spr.txt", "prize-cool") == 0 &&
        RM.loadSound("sounds/crate-drop.wav", "crate-drop") == 0 &&
        RM.loadSound("sounds/crate-stack.wav", "crate-stack") == 0 &&
        RM.loadSound("sounds/crate-explode.wav", "crate-explode") == 0 &&
        RM.loadMusic("sounds/menu-music.wav", "menu-music") == 0 &&
        RM.loadMusic("sounds/game-music.wav", "game-music") == 0 &&
        RM.loadMusic("sounds/prize-music.wav", "prize-music") == 0
    ) ? 0 : -1;
}