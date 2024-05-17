#ifndef GBGAME_SCORES_H
#define GBGAME_SCORES_H
//#include <vector>
#include <cstdint>
#include <unordered_map>
#include "states/globalStates.h"


class State;

class Scores {
public:
    static Scores& getInstance(); // Method to get the singleton instance

    void addScore(uint8_t score, State *gameThatWasPlayed); // Add a score to the list
    void init();

    std::unordered_map<uint32_t,uint8_t>maxScores;
    uint8_t leaderBoards[GlobalStates::numberOfGameStates][5];

    // Delete copy constructor and copy assignment operator

    Scores(const Scores&) = delete;
    Scores& operator=(const Scores&) = delete;

private:
    Scores();  // Private constructor
    ~Scores(); // Private destructor
   // std::vector<uint8_t> maxScores; // Vector to store scores
  //  uint8_t maxScores[GlobalStates::numberOfGameStates];

};


#endif //GBGAME_SCORES_H
