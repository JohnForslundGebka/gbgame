#include "mainMenu.h"

void MainMenu::handleInput() {
    while (m_isRunning && Buttons::states.wait_any(Buttons::UP_FLAG | Buttons::DOWN_FLAG, osWaitForever, false)) {

    }
}

void MainMenu::update() {

}

void MainMenu::run() {

}

void MainMenu::stop() {

}

MainMenu::MainMenu() : m_textCanvas(128,128,0,0), m_handCanvas(16,11,7,30) {}
