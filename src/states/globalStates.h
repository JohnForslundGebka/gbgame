#ifndef GBGAME_GLOBALSTATES_H
#define GBGAME_GLOBALSTATES_H
#include <cstdint>

class MainMenu;
class DistanceGame;
class State;


namespace GlobalStates {
    extern MainMenu mainMenu;
    extern DistanceGame distanceGame;
    extern State* stateList[2];

    extern const uint32_t ALL_STATE_FLAGS;
}

#endif //GBGAME_GLOBALSTATES_H

