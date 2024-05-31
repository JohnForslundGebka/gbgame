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

void MultiplayerMenuUI::drawLobbyList() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("Lobby");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);   

    int cursorPosition = 30;
    int index = 0;
    c_main.C.setTextSize(1);
    for (auto &challenge : parentState->m_lobbyList){
        c_main.C.setTextColor((*parentState->m_optionPtr == index) ? GREEN : 0x738E);

        c_main.C.setCursor(4, cursorPosition);
        c_main.C.print(challenge->m_challengeSummery);

        cursorPosition += 12;
        index++;
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
//draw my games screen
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

    int index = 0;
    uint16_t color{};
    c_main.C.setTextSize(1);
    for (auto &challenge : parentState->m_myGamesList){

        challenge->m_played ? color = GREEN : color = RED;
        c_main.C.setTextColor((*parentState->m_optionPtr == index) ? GREEN : 0x738E);

        c_main.C.setCursor(4, cursorPosition);
        c_main.C.print(challenge->m_challengeSummery);
        c_main.C.fillCircle(94, cursorPosition+3, 2, color);
        cursorPosition += 10;
        index++;
    }
}

void MultiplayerMenuUI::drawNotConnectedScreen() {
    c_main.C.fillScreen(BLACK);
    c_main.C.drawBitmap(43, 76, image_Restoring_bits, 38, 32, 0xFFFF);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(25, 4);
    c_main.C.print("Please ");
    c_main.C.setCursor(24, 21);
    c_main.C.print("connect");
    c_main.C.setCursor(23, 40);
    c_main.C.print("to wifi");
    c_main.C.setTextSize(1);
    c_main.C.setCursor(21, 59);
    c_main.C.print("for mulitplayer");
}
void MultiplayerMenuUI::drawWaitingScreen() {
    c_main.C.fillScreen(BLACK);
    c_main.C.drawBitmap(43, 76, image_Restoring_bits, 38, 32, 0xFFFF);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(3, 25);
    c_main.C.print("Waiting... ");
}

void MultiplayerMenuUI::drawChallengeInfo(Challenge* challenge) {

    ChallengeHandler &challengeHandler = ChallengeHandler::getInstance();
    DataTransmit &wifi = DataTransmit::getInstance();

    c_main.C.fillScreen(BLACK);
    c_main.C.drawLine(0, 19, 127, 19, 0xFFFF);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(11, 2);
    c_main.C.print("Challenge");
    c_main.C.setTextColor(0x57FF);
    c_main.C.setCursor(37, 29);
    c_main.C.print(challenge->m_game);
    c_main.C.setTextColor(0xFABF);
    c_main.C.setCursor(4, 53);
    c_main.C.print(challenge->m_player1Name);


    c_main.C.setTextColor(0x540);
    c_main.C.setCursor(95, 53);
    c_main.C.print(challenge->m_player1Score);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(1);
    c_main.C.setCursor(38, 105);

    if (challenge->m_played) {
        c_main.C.setCursor(4, 74);
        c_main.C.print(challenge->m_player2Name);
        c_main.C.setCursor(95, 74);
        c_main.C.print(challenge->m_player2Score);

        if (wifi.userName == challenge->m_winner) {
            c_main.C.print("You won!");
        } else {
            c_main.C.print("You lost!");
        }



    } else {
        c_main.C.print("Not played!");
    }



}




