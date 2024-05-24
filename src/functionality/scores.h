/**
 * @brief this class is responsible for handling all the scores from the games
 *
 *
 * @param leaderBoards is an map, with the key  being the type of game, and the value is an array of scores and names
 */
#ifndef GBGAME_SCORES_H
#define GBGAME_SCORES_H
#include <cstdint>
#include <unordered_map>
#include <array>
#include "states/globalStates.h"
#include "wifi/dataTransmit.h"
#include "core/settings.h"
#include "states/newHighscore/newHighscore.h"

class State;

class Scores {
public:
    static Scores& getInstance(); // Method to get the singleton instance

    /**
     * @brief Adds a new score for a given game state.
     * @param score The score to add.
     * @param gameThatWasPlayed Pointer to the game state for which the score is added.
     * @return True if the score is a new high score, false otherwise.
     */
    bool addScore(int score, State *gameThatWasPlayed); // Add a score to the list

    /**
     * @brief Attempts to add a score to the leaderboard.
     * @param score The score to add.
     * @param playedGame The identifier of the game the score belongs to.
     * @return True if the score was successfully added, false otherwise.
     */
    bool addScoreToLeaderboard(int score, uint32_t playedGame);
      /**
      * @brief Retrieves leaderboard data from the database.
      */
    void getLeaderboardFromDatabase();
    /**
     * @brief Initializes scores and leaderboards, connects to database if available.
     */
    void init();

    std::unordered_map<uint32_t,int>maxScores;

    /**
     * @brief Holds the top scores for all game states.
     *
     * Maps each game state identified by a unique uint32_t ID to an array of top five scores. Each entry in the array is a
     * pair consisting of a player's name and their score.
     *
     * @details
     * - `LeaderboardEntry`: A pair representing a single score entry, containing the player's name (`String`) and their score (`int`).
     * - `ScoresArray`: An array of five `LeaderboardEntry` elements, representing the top five scores for a game state.
     * - `leaderBoards`: A hash map where each key is a game state ID (`uint32_t`) and the value is a `ScoresArray` containing the top scores for that state.
     */
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
