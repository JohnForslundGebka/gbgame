
/**
 * @brief This is the wifi menu state. It has the following functionality:
 * - Let's the user scan and choose network 
 * - Enter network password
 * - Enter username displayed in challenges and highscore boards. 
 * - Connect to the network using the saved network name and password. 
 * 
 * The network name, password and user name are saved to flash memory and are saved
 * between power on/off so if the user is connecting to the same network it's possible login directly
 * using the Login option in the menu.
 */

#ifndef GBGAME_wifiMenu_H
#define GBGAME_wifiMenu_H

#include <Arduino.h>
#include <vector>
#include "core/macros.h"
#include "mbed.h"
#include "rtos.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "hardware/displayManager.h"
#include "wifiMenuUI.h"
#include "functionality/readWriteFlash.h"
#include "core/settings.h"
#include "wifi/dataTransmit.h"

class WifiMenu : public State {
private:
    rtos::Thread *t_gameLogic = nullptr;        //Thread that handles the game logic/order
    rtos::Thread *t_userInput = nullptr;        //Thread that handles user input
    rtos::Thread *t_screenUpdate = nullptr;     //This thread is responsible for updating the screen when the SCREEN_UPDATE_FLAG is set (highest priority)

    rtos::EventFlags m_gameFlags;    //Contains flags ADVANCE_GAME_FLAG and SCREEN_UPDATE_FLAG

    //Canvas object for drawing the screens
    WifiMenuUI *m_canvas = nullptr;

    enum {
        LOGIN_LAST,
        NEW_WIFI,
        PASSWORD,
        SET_NAME
    };

public:
    DataTransmit &wifi = DataTransmit::getInstance();
    std::vector<String> m_networkList;

    char m_username[5] = {'A', 'A', 'A', 'A', '\0'};
    char m_password[15] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
    char *p_selectedText = m_username;

    std::string m_string_password = " ";
    std::string m_saved_network = " ";

    bool m_optionEntered = false;
    bool m_execute = false;
    bool m_getNetworks = true;

    int m_option = 0;
    int m_optionMAX = 3;

    int m_selectedNetwork = 0; 


    int m_selectedLetter = 0;
    int m_maxLetter = 4;

    int m_minASCII = 65;
    int m_maxASCII = 122;

    bool m_firstRun = true;

    WifiMenu();

    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;

    void game();                          //Contains the logic for the game

    void setName();
    void checkLetterBounds(char &letter);

    void setASCIIBounds(int min, int max);
    void updatePasswordString();

};

#endif //GBGAME_wifiMenu_H
