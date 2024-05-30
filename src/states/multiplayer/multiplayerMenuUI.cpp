#include "multiplayerMenuUI.h"
#include "multiplayerMenu.h"
#include "functionality/challengeHandler.h"
#include "wifi/dataTransmit.h"


MultiplayerMenuUI::MultiplayerMenuUI(MultiplayerMenu *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {
}

void MultiplayerMenuUI::init() {}

//Exit screen
void MultiplayerMenuUI::drawScreen1() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(MAGENTA);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(1, 3);
    c_main.C.print("Multiplayer");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);                                //Draw line under "Wifi"

    //Draw menu options
    int cursorPosition = 33;
    c_main.C.setCursor(1, cursorPosition);
        

    int index = 0; // Manual index to replace 'i' in the original for-loop
    for (const auto& option : m_menuOptions) {
        // Sets color of selected option
        c_main.C.setTextColor(*parentState->m_optionPtr == index ? GREEN : 0x738E);

        c_main.C.print(option);
        cursorPosition += 30;
        c_main.C.setCursor(4, cursorPosition);

        index++; // Increment the manual index
    }
    
}

//password screen
void MultiplayerMenuUI::drawScreen2() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("Lobby");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);   

    int cursorPosition = 30;

    c_main.C.setTextSize(1);
    for (int i = 0; i < parentState -> m_lobbyList.size(); i++) {
        //Sets color of selected option
        c_main.C.setTextColor(*parentState->m_optionPtr == i ? GREEN : 0x738E);

        c_main.C.setCursor(4, cursorPosition);
        c_main.C.print(parentState -> m_lobbyList[i]);
        
        cursorPosition += 25;
    }
 

}

void MultiplayerMenuUI::drawScreen3() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(20, 3);
    c_main.C.print("New Game");
    c_main.C.drawLine(0, 20, 128, 20, WHITE);    

    c_main.C.setTextColor(GREEN);

    c_main.C.setCursor(20, 40);
    c_main.C.print("Press A");
    c_main.C.setCursor(8, 65);
    c_main.C.print("and choose");
    c_main.C.setCursor(25, 90);
    c_main.C.print("a game! ");
    
}

void MultiplayerMenuUI::drawScreen4() {
    ChallengeHandler &challengeHandler = ChallengeHandler::getInstance();
    DataTransmit &wifi = DataTransmit::getInstance();

    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("My games");
    c_main.C.drawLine(0, 20, 128, 20, WHITE);    

    int cursorPosition = 30;

    std::vector<Challenge> myChallenges;

    for (auto &challenge : challengeHandler.challenges)
    {
        if(challenge.m_player1Name == wifi.userName) {
            myChallenges.push_back(challenge);
        }
    }

    int index = 0;
    c_main.C.setTextSize(1);
    for (auto &challenge : myChallenges){
        c_main.C.setTextColor(*parentState->m_optionPtr == index ? GREEN : 0x738E);

        c_main.C.setCursor(4, cursorPosition);
        c_main.C.print(challenge.m_challengeSummery);

        cursorPosition += 12;
        index++;
    }


//    for (int i = 0; i < parentState -> m_myGamesList.size(); i++) {
//        //Sets color of selected option
//        c_main.C.setTextColor(*parentState->m_optionPtr == i ? GREEN : 0x738E);
//
//        c_main.C.setCursor(4, cursorPosition);
//        c_main.C.print(parentState -> m_myGamesList[i]);
//
//        cursorPosition += 25;
//    }
    
}




