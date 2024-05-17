#ifndef GBGAME_SCORES_H
#define GBGAME_SCORES_H
#include <cstdint>
#include <unordered_map>
#include <array>
#include "states/globalStates.h"
#include "wifi/dataTransmit.h"
#include "core/settings.h"

class State;

class Scores {
public:
    static Scores& getInstance(); // Method to get the singleton instance

    void addScore(int score, State *gameThatWasPlayed); // Add a score to the list
    void addScoreToDatabase(State *gameThatWasPlayed);
    void getLeaderboardFromDatabase();
    void init();

    std::unordered_map<uint32_t,int>maxScores;
    //  uint8_t leaderBoards[GlobalStates::numberOfGameStates][5];
    //   std::pair<String,int>leaderBoards[GlobalStates::numberOfGameStates][5];

    // Define the type for the leaderboard entry
    using LeaderboardEntry = std::pair<String, int>;
    // Define the type for the scores array, containing 5 top scores
    using ScoresArray = std::array<LeaderboardEntry, 5>;

    // Define the map to hold all game states with their respective scores
    std::unordered_map<uint32_t, ScoresArray> leaderBoards;


    // Delete copy constructor and copy assignment operator
    Scores(const Scores&) = delete;
    Scores& operator=(const Scores&) = delete;

private:
    Scores();  // Private constructor
    ~Scores(); // Private destructor
    DataTransmit &dataTransmit = DataTransmit::getInstance();
};


#endif //GBGAME_SCORES_H
