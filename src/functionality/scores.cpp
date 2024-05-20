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

    bool wasAddedToLeaderboard = false;

    uint32_t playedGame = gameThatWasPlayed->getFlagName();
    if(score > maxScores[playedGame]){

        wasAddedToLeaderboard = addScoreToDatabase(score,playedGame);

        Serial.println( );
        Serial.print("NEW RECORD: SCORE WAS ");
        Serial.println(score);
    }
}

void Scores::init() {

    getLeaderboardFromDatabase();

    //set all the current scores to 0
    for(auto &game : GlobalStates::gameList)
    {
        uint32_t  playedGame = game->getFlagName();
        maxScores.emplace(playedGame,leaderBoards[playedGame][4].second);
    }

}

void Scores::getLeaderboardFromDatabase() {
    dataTransmit.getDataToHighscore(leaderBoards);

#ifdef DEBUG
    Serial.print("PRINTING LEADERBOARD:------ ");
    for (int i = 0; i < GlobalStates::numberOfGameStates; i++){

        for(int j = 0; j < 5; j++){
            Serial.print(leaderBoards[i][j].first);
            Serial.print("    ---> ");
            Serial.println(leaderBoards[i][j].second);
        }
    }
#endif
}

bool Scores::addScoreToDatabase(int newScore, uint32_t playedGame) {

    //update the leaderboard from Database
    getLeaderboardFromDatabase();

    //Early exit if the new score is not higher than the lowest score on the board.
    if (newScore <= leaderBoards[playedGame][4].second) {
        maxScores[playedGame] = leaderBoards[playedGame][4].second;
        return false;
    }

    //the starting position of our iteration through the list
    int pos = 4;

    while (pos > 0 && newScore > leaderBoards[playedGame][pos - 1].second) {
        leaderBoards[playedGame][pos] = leaderBoards[playedGame][pos - 1]; // Shift scores down
        pos--;
    }
    // Insert the new score at the found position
    leaderBoards[playedGame][pos] = std::make_pair(GlobalSettings::userName, newScore);

    //make the 5th score the current highest score
    maxScores[playedGame] = leaderBoards[playedGame][4].second;

    return true;
}
