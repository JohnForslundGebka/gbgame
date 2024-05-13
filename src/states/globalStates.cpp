#include "globalStates.h"
#include "core/state.h"
#include "states/distanceGame/distanceGame.h"
#include "states/mainMenu/mainMenu.h"
#include "states/subMenuGames/games.h"

//all available states
namespace GlobalStates {
    MainMenu mainMenu;
    DistanceGame distanceGame;
    Games games;

    State* stateList[numberOfTotalStates] = {&mainMenu, &distanceGame, &games};

    State* mainMenuList[numberOfMainMenuStates] = {&games};

    State* gameList[numberOfGameStates] = {&distanceGame};

    const uint32_t ALL_STATE_FLAGS = mainMenu.getFlagName() | distanceGame.getFlagName() | games.getFlagName();

}