/**
 * @class NewHighscore
 * @brief Displays the users score and plays an animation
 *
 * After the state has finished running, it will start the Highscore state
 */
#ifndef GBGAME_NEWHIGHSCORE_H
#define GBGAME_NEWHIGHSCORE_H
#include "core/state.h"
#include "newHighscoreUi.h"

class NewHighscore : public State{
public:
    void handleInput() override;

    void update() override;

    void dance(); //manages the animation on the screen

    void run() override;

    void stop() override; //cleans up all the resources used in the state

    explicit NewHighscore();

    void setScore(int score); //sets the user score that will be shown on the screen

private:
    NewHighscoreUi* c_canvas = nullptr;
    Canvas* m_pntrCanvas = nullptr;

    int m_score = 0;

    //threads that will be running in this state
    rtos::Thread* t_gfx = nullptr;
    rtos::Thread* t_move= nullptr;
    rtos::Thread* t_dance = nullptr;
    class rtos::EventFlags m_gameFlags;
};


#endif //GBGAME_NEWHIGHSCORE_H
