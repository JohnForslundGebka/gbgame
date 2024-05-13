#include "globalStates.h"
#include "core/state.h"
#include "states/distanceGame/distanceGame.h"
#include "states/mainMenu/mainMenu.h"

//all available states
namespace GlobalStates {
    MainMenu mainMenu;
    DistanceGame distanceGame;
    State* stateList[2] = {&mainMenu, &distanceGame};

    const uint32_t ALL_STATE_FLAGS = mainMenu.getFlagName() | distanceGame.getFlagName();
}