#include "globalStates.h"
#include "core/state.h"
#include "states/distanceGame/distanceGame.h"
#include "states/mainMenu/mainMenu.h"
#include "states/subMenuGames/games.h"
#include "states/settings/settings.h"


namespace GlobalStates {
    //all available states
    MainMenu mainMenu;
    DistanceGame distanceGame;
    Games games;
    Settings settings;

    State* stateList[numberOfTotalStates] = {&mainMenu, &distanceGame, &games, &settings};

    State* mainMenuList[numberOfMainMenuStates] = {&games,&settings};
    State* gameList[numberOfGameStates] = {&distanceGame};
    State* settingsList[numberOfSettingsStates];

    //variable used be the State handler to change state
    const uint32_t ALL_STATE_FLAGS = mainMenu.getFlagName() |
                                 distanceGame.getFlagName() |
                                        games.getFlagName() |
                                     settings.getFlagName();
}