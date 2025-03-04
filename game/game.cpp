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
        RM.loadSprite("sprites/highest-point-spr.txt", "highest-point") == 0
    ) ? 0 : -1;
}