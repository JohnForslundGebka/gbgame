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

void Scores::addScore(int score,State *gameThatWasPlayed) {

    uint32_t playedGame = gameThatWasPlayed->getFlagName();
    if(score > maxScores[playedGame]){
        maxScores[playedGame] = score;
        Serial.println( );
        Serial.print("NEW RECORD: SCORE WAS ");
        Serial.println(score);
    }
}

void Scores::init() {
    //set all the current scores to 0
    for(auto &game : GlobalStates::gameList)
    {
        maxScores.emplace(game->getFlagName(),0);
    }
}

void Scores::getLeaderboardFromDatabase() {
    dataTransmit.getDataToHighscore(leaderBoards);

    Serial.print("PRINTING LEADERBOARD:------ ");
    for (int i = 0; i < GlobalStates::numberOfGameStates; i++){

        for(int j = 0; j < 5; j++){
            Serial.print(leaderBoards[i][j].first);
            Serial.print("    ---> ");
            Serial.println(leaderBoards[i][j].second);
        }
    }
}

