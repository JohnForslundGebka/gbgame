
/**
 * @brief namespace that contains all instances of states
 *
 *
 * @param stateList is an array of all possible states
 */
#ifndef GBGAME_GLOBALSTATES_H
#define GBGAME_GLOBALSTATES_H
#include <cstdint>

class MainMenu;
class DistanceGame;
class State;
class Games;
class Settings;

namespace GlobalStates {

    const int numberOfTotalStates = 4;
    const int numberOfMainMenuStates = 2;
    const int numberOfGameStates = 1;
    const int numberOfSettingsStates = 3;

    //all different states on the machine
    extern MainMenu mainMenu;
    extern DistanceGame distanceGame;
    extern Games games;
    extern Settings settings;

    //arrays of different states, used for menus
    extern State* stateList[numberOfTotalStates];
    extern State* mainMenuList[numberOfMainMenuStates];
    extern State* gameList[numberOfGameStates];
    extern State* settingsList[numberOfSettingsStates];

    extern const uint32_t ALL_STATE_FLAGS;
}

#endif //GBGAME_GLOBALSTATES_H

