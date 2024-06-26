#include "globalStates.h"
#include "core/state.h"
#include "states/distanceGame/distanceGame.h"
#include "states/mainMenu/mainMenu.h"
#include "states/subMenuGames/games.h"
#include "states/settings/settings.h"

#include "states/micGame/micGame.h"
#include "states/highscore/highScore.h"
#include "states/newHighscore/newHighscore.h"
#include "states/wifiMenu/wifiMenu.h"
#include "states/multiplayer/multiplayerMenu.h"
#include "states/gyroscopeGame/gyroscopeGame.h"




namespace GlobalStates {
    //all available states
    MainMenu mainMenu;
    DistanceGame distanceGame;
    Games games;
    Settings settings;

    MicGame micGame;
    HighScore highScore;
    NewHighscore newHighscore;
    WifiMenu wifiMenu;
    MultiplayerMenu multiplayerMenu;
    GyroscopeGame gyroscopeGame;

    State* stateList[numberOfTotalStates] = {&mainMenu, &distanceGame, &games, &settings, &micGame, &highScore, &newHighscore, &wifiMenu, &multiplayerMenu, &gyroscopeGame};

    State* mainMenuList[numberOfMainMenuStates] = {&games,&settings,&highScore, &multiplayerMenu};
    State* gameList[numberOfGameStates] = {&distanceGame, &micGame, &gyroscopeGame};
    State* settingsList[numberOfSettingsStates] = {&wifiMenu};

    //variable used be the State handler to change state
    const uint32_t ALL_STATE_FLAGS = mainMenu.getFlagName() |
                                 distanceGame.getFlagName() |
                                        games.getFlagName() |
                                     settings.getFlagName() |
                                     micGame.getFlagName()  |
                                     highScore.getFlagName()|
                                     newHighscore.getFlagName() |
                                     wifiMenu.getFlagName() |
                                     multiplayerMenu.getFlagName()|
                                     gyroscopeGame.getFlagName();
}