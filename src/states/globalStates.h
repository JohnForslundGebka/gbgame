
/**
 * @brief namespace that contains all instances of states
 *
 *
 * @param stateList is an array of all possible states
 */
#ifndef GBGAME_GLOBALSTATES_H
#define GBGAME_GLOBALSTATES_H
#include <cstdint>

class Settings;
class MainMenu;
class DistanceGame;
class Games;
class MicGame;
class HighScore;
class NewHighscore;
class WifiMenu;
class MultiplayerMenu;


// Not a state, just the base class
class State;


namespace GlobalStates {

    const int numberOfTotalStates = 9;
    const int numberOfMainMenuStates = 4;
    const int numberOfGameStates = 2;
    const int numberOfSettingsStates = 1;

    //all different states on the machine
    extern MainMenu mainMenu;
    extern DistanceGame distanceGame;
    extern Games games;
    extern Settings settings;
    extern MicGame micGame;
    extern HighScore highScore;
    extern NewHighscore newHighscore;
    extern WifiMenu wifiMenu;
    extern MultiplayerMenu multiplayerMenu;

    


    //arrays of different states, used for menus
    extern State* stateList[numberOfTotalStates];
    extern State* mainMenuList[numberOfMainMenuStates];
    extern State* gameList[numberOfGameStates];
    extern State* settingsList[numberOfSettingsStates];

    extern const uint32_t ALL_STATE_FLAGS;
}

#endif //GBGAME_GLOBALSTATES_H

