
/**
 * @brief 
 * 
 * @class
 */

#ifndef GBGAME_MULTIPLAYER_H
#define GBGAME_MULTIPLAYER_H
#include <Arduino.h>
#include <vector>
#include "core/macros.h"
#include "mbed.h"
#include "rtos.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "hardware/displayManager.h"
#include "multiplayerMenuUI.h"
#include "functionality/challenge.h"
#include "wifi/dataTransmit.h"

class MultiplayerMenu : public State {
private:
    rtos::Thread *t_gameLogic = nullptr;        //Thread that handles the game logic/order
    rtos::Thread *t_userInput = nullptr;        //Thread that handles user input
    rtos::Thread *t_screenUpdate = nullptr;     //This thread is responsible for updating the screen when the SCREEN_UPDATE_FLAG is set (highest priority)

    rtos::EventFlags m_gameFlags;    //Contains flags ADVANCE_GAME_FLAG and SCREEN_UPDATE_FLAG

    //Canvas object for drawing the screens
    MultiplayerMenuUI *m_canvas = nullptr;
    DataTransmit &wifi = DataTransmit::getInstance();

    enum {
        LOBBY,
        NEW,
        MY_GAMES,
    };

public:
    std::vector<String> m_lobbyList;
    std::vector<String> m_newList = {"Voicy", "Measury"};
    std::vector<String> m_myGamesList = {"Voicy", "Measury", "Voicy"};

    bool m_optionEntered = false;
    bool m_execute = false;

    int m_option = 0;
    int m_optionMAX = 3;

    MultiplayerMenu();

    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;

    void game();                          //Contains the logic for the game

};

#endif //GBGAME_MULTIPLAYER_H
