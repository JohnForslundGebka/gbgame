#ifndef GBGAME_GLOBALSTATES_H
#define GBGAME_GLOBALSTATES_H


class MainMenu;
class DistanceGame;
class State;

namespace GlobalStates {
    extern MainMenu mainMenu;
    extern DistanceGame distanceGame;
    extern State* stateList[2];
}

#endif //GBGAME_GLOBALSTATES_H

