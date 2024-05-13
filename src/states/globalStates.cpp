#include "globalStates.h"
#include "core/state.h"
#include "states/distanceGame/distanceGame.h"
#include "states/mainMenu/mainMenu.h"
#include "states/subMenuGames/games.h"
#include "states/settings/settings.h"

//all available states
namespace GlobalStates {
    MainMenu mainMenu;
    DistanceGame distanceGame;
    Games games;
    Settings settings;

    State* stateList[numberOfTotalStates] = {&mainMenu, &distanceGame, &games, &settings};

    State* mainMenuList[numberOfMainMenuStates] = {&games};
    State* gameList[numberOfGameStates] = {&distanceGame};
    State* settingsList[numberOfSettingsStates] ={};
    
    const uint32_t ALL_STATE_FLAGS = mainMenu.getFlagName() |
                                 distanceGame.getFlagName() |
                                        games.getFlagName() |
                                     settings.getFlagName();
}