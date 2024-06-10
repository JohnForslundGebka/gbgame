#include "scores.h"
#include "core/state.h"
#include <algorithm>


Scores::Scores() {
}

Scores::~Scores() {
}

Scores& Scores::getInstance() {
    static Scores instance; // Guaranteed to be destroyed and instantiated on first use.
    return instance;
}

bool Scores::checkIfScoreWasHighcore(int score, State *gameThatWasPlayed) {
    // Get the flag of the game that was played
    uint32_t playedGame = gameThatWasPlayed->getFlagName();

    // Check if the score is greater than the maximum score for the played game
    if(score > maxScores[playedGame]) {
        // Attempt to add the score to the leaderboard
        bool scoreAdded = addScoreToLeaderboard(score, playedGame);

        // If the score was successfully added, set the new high score
        if (scoreAdded) {
            GlobalStates::newHighscore.setScore(score);
        }
        return scoreAdded;
    } else {
        // If the score is not greater than the maximum score, return false
        return false;
    }
}

void Scores::init() {
    // Define the type for the leaderboard entry
    using LeaderboardEntry = std::pair<String, int>;
    // Define the type for the scores array, containing 5 top scores
    using ScoresArray = std::array<LeaderboardEntry, 5>;
    // Define the map to hold all game states with their respective scores
    std::unordered_map<uint32_t, ScoresArray> leaderBoards;

    //if the unit is connected to Wi-Fi, update the leaderboard with the values from the database
    if(dataTransmit.wifiIsConnected) {
        //set all the current scores
        dataTransmit.getDataToHighscore(leaderBoards);

        //fill the local map with the lowest score on the leaderboard
        for (auto &game: GlobalStates::gameList) {
            uint32_t playedGame = game->getFlagName();
            maxScores.emplace(playedGame, leaderBoards[playedGame][4].second);
        }
    }else {
#ifdef DEBUG
        Serial.println("wifi is not connected!!");
#endif
        // is the unit is not connected to Wi-Fi, init everything to 0
        //fill the local scores with 0
    for(auto &game:GlobalStates::gameList){
       uint32_t playedGame = game->getFlagName();
       maxScores.emplace(playedGame,1);
    }

    }


}

void Scores::getLeaderboardFromDatabase() {
    // Define the type for the leaderboard entry
    using LeaderboardEntry = std::pair<String, int>;
    // Define the type for the scores array, containing 5 top scores
    using ScoresArray = std::array<LeaderboardEntry, 5>;
    // Define the map to hold all game states with their respective scores
    std::unordered_map<uint32_t, ScoresArray> leaderBoards;

    dataTransmit.getDataToHighscore(leaderBoards);
    //fill the local map with the lowest score on the leaderboard
    for (auto &game: GlobalStates::gameList) {
        uint32_t playedGame = game->getFlagName();
        maxScores.emplace(playedGame, leaderBoards[playedGame][4].second);
    }

}

bool Scores::addScoreToLeaderboard(int score, uint32_t playedGame) {

    // Define the type for the leaderboard entry
    using LeaderboardEntry = std::pair<String, int>;
    // Define the type for the scores array, containing 5 top scores
    using ScoresArray = std::array<LeaderboardEntry, 5>;
    // Define the map to hold all game states with their respective scores
    std::unordered_map<uint32_t, ScoresArray> leaderBoards;

    //fill the map with temp values
    for (auto & game : GlobalStates::gameList){
        uint32_t gameKey = game->getFlagName();
        int score = 5;
        for (int j = 0; j < 5; j++){
            leaderBoards[gameKey][j] = std::make_pair("-", score);
            score--;
        }
    }

    if(dataTransmit.wifiIsConnected){
    //update the leaderboard from Database
    dataTransmit.getDataToHighscore(leaderBoards);
    }

    //Early exit if the new score is not higher than the lowest score on the board.
    if (score <= leaderBoards[playedGame][4].second) {
        maxScores[playedGame] = leaderBoards[playedGame][4].second;
        return false;
    }

    //the starting position of our iteration through the list
    int pos = 4;

    while (pos > 0 && score > leaderBoards[playedGame][pos - 1].second) {
        leaderBoards[playedGame][pos] = leaderBoards[playedGame][pos - 1]; // Shift scores down
        pos--;
    }

    Serial.print("NU LÄGGER VI IN NAMNET I HIGHSCORE->");
    Serial.println(dataTransmit.userName);
    // Insert the new score at the found position
    leaderBoards[playedGame][pos] = std::make_pair(dataTransmit.userName, score);

    //make the 5th score the current highest score
    maxScores[playedGame] = leaderBoards[playedGame][4].second;
    if(dataTransmit.wifiIsConnected) {
        dataTransmit.sendHighscoreToData(leaderBoards);
    }
    return true;
}
