#ifndef GBGAME_GLOBALSTATES_H
#define GBGAME_GLOBALSTATES_H
#include <cstdint>

class MainMenu;
class DistanceGame;
class State;
class Games;

namespace GlobalStates {

    const int numberOfTotalStates = 3;
    const int numberOfMainMenuStates = 1;
    const int numberOfGameStates = 1;

    extern MainMenu mainMenu;
    extern DistanceGame distanceGame;
    extern Games games;
    extern State* stateList[numberOfTotalStates];
    extern State* mainMenuList[numberOfMainMenuStates];
    extern State* gameList[numberOfGameStates];

    extern const uint32_t ALL_STATE_FLAGS;
}

#endif //GBGAME_GLOBALSTATES_H

