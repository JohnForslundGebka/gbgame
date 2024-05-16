#include "scores.h"
#include "core/state.h"
#include <algorithm> // For std::max_element

Scores::Scores() {
    // Constructor can initialize any required elements
}

Scores::~Scores() {
    // Cleanup code if necessary
}

Scores& Scores::getInstance() {
    static Scores instance; // Guaranteed to be destroyed and instantiated on first use.
    return instance;
}

void Scores::addScore(uint8_t score,State *gameThatWasPlayed) {

    if(score > maxScores.at(gameThatWasPlayed->getFlagName())){
        maxScores.emplace(gameThatWasPlayed->getFlagName(),score);
    }
}

void Scores::init() {
    //set all the current scores to 0
    for(auto &game : GlobalStates::gameList)
    {
        maxScores.emplace(game->getFlagName(),0);
    }
}







//int Scores::getHighestScore() const {
//    if (scores.empty()) return 0; // Return 0 if no scores are present
//    return *std::max_element(scores.begin(), scores.end());
//}
//
//std::vector<int> Scores::getAllScores() const {
//    return scores;
//
//}