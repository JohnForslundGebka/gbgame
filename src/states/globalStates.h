#ifndef GBGAME_GLOBALSTATES_H
#define GBGAME_GLOBALSTATES_H
#include <cstdint>

class MainMenu;
class DistanceGame;
class State;

namespace GlobalStates {

    const int numberOfTotalStates = 2;
    const int numberOfMainMenuStates = 4;

    extern MainMenu mainMenu;
    extern DistanceGame distanceGame;
    extern State* stateList[numberOfTotalStates];
    extern State* mainMenuList[numberOfMainMenuStates];

    extern const uint32_t ALL_STATE_FLAGS;
}

#endif //GBGAME_GLOBALSTATES_H

