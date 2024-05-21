#include "globalStates.h"
#include "core/state.h"
#include "states/distanceGame/distanceGame.h"
#include "states/mainMenu/mainMenu.h"
#include "states/subMenuGames/games.h"
#include "states/settings/settings.h"
#include "states/micGame/micGame.h"
#include "states/wifiMenu/wifiMenu.h"



namespace GlobalStates {
    //all available states
    MainMenu mainMenu;
    DistanceGame distanceGame;
    Games games;
    Settings settings;
    MicGame micGame;
    WifiMenu wifiMenu;


    State* stateList[numberOfTotalStates] = {&mainMenu, &distanceGame, &games, &settings, &micGame, &wifiMenu};

    State* mainMenuList[numberOfMainMenuStates] = {&games,&settings};
    State* gameList[numberOfGameStates] = {&distanceGame, &micGame};
    State* settingsList[numberOfSettingsStates] = {&wifiMenu};

    //variable used be the State handler to change state
    const uint32_t ALL_STATE_FLAGS = mainMenu.getFlagName() |
                                 distanceGame.getFlagName() |
                                        games.getFlagName() |
                                     settings.getFlagName() |
                                     micGame.getFlagName()  |
                                     wifiMenu.getFlagName();
}