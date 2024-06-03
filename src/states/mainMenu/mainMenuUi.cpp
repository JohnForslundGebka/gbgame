#include "mainMenuUi.h"
#include "mainMenu.h"
#include "wifi/dataTransmit.h"


MainMenuUi::MainMenuUi(MainMenu *p) : c_canvas(128,128,0,0), parentState(p) {
}


void MainMenuUi::drawText(){
    int counter = parentState->m_selectedState;
    String text = GlobalStates::mainMenuList[counter]->m_stateName;

    DataTransmit &dataTransmit = DataTransmit::getInstance();
   //  updateTextFields();
     c_canvas.C.fillScreen(BLACK);

    c_canvas.C.setTextColor(WHITE);
    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextWrap(false);
    c_canvas.C.setCursor(18, 0);
    c_canvas.C.print("-GbgGame-");

    c_canvas.C.drawLine(1, 18, 128, 18, 0xFFFF);
    if(dataTransmit.wifiIsConnected) {
        c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, BLUE);
    } else {
        c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, WHITE);
    }

    // Calculate the width of the text
    int16_t x1, y1;
    uint16_t w, h;
    c_canvas.C.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

    // Calculate x position to center the text
    int16_t x = (128 - w) / 2;
   if(text == "Multiplayer"){
       x += 3;
   }

    // Set the cursor to the calculated position and print the text
    c_canvas.C.setTextColor(GREEN);
    c_canvas.C.setCursor(x, 66);
    c_canvas.C.print(text);
    // Draw the arrows and pictures
    c_canvas.C.drawBitmap(55, 42, image_ArrowUpEmpty_bits, 14, 15, 0xFFFF);
    c_canvas.C.drawBitmap(55, 91, image_ArrowDownEmpty_bits, 14, 15, 0xFFFF);
    c_canvas.C.drawBitmap(64, 104, image_resized_tram_32x32_bits, 32, 32, 0xFFFF);
    c_canvas.C.drawBitmap(32, 111, image_tree_bits, 16, 16, 0xFFFF);


}


void MainMenuUi::moveDown() {
     drawText();
}

void MainMenuUi::moveUp() {
    drawText();
}


