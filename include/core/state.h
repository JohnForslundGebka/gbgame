#ifndef GBGAME_STATE_H
#define GBGAME_STATE_H
class State {
    //Virtual functions that handles inputs and updates
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void run() = 0;
};

#endif //GBGAME_STATE_H
