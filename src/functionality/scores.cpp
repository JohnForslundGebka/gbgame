#include "scores.h"
#include "core/state.h"
#include <algorithm> // For std::max_element


Scores::Scores() {
}

Scores::~Scores() {
}

Scores& Scores::getInstance() {
    static Scores instance; // Guaranteed to be destroyed and instantiated on first use.
    return instance;
}

void Scores::addScore(int score,State *gameThatWasPlayed) {

    //get the flag of the game the was played
    uint32_t playedGame = gameThatWasPlayed->getFlagName();
      //if the user has set a new high score
      if(score > maxScores[playedGame]) {
       //if the unit is connected to wifi, try to add the score to the leaderboard
          if (GlobalStates::wifiIsConnected) {
              if (addScoreToDatabase(score, playedGame)) {
                  //this is used for testing
#ifdef DEBUG
                  Serial.print("PRINTING LEADERBOARD AFTER UPDATE:");
                  for (int i = 0; i < GlobalStates::numberOfGameStates; i++) {
                      uint32_t gameKey = GlobalStates::gameList[i]->getFlagName();
                      Serial.println(" ");
                      for (int j = 0; j < 5; j++) {
                          Serial.print(leaderBoards[gameKey][j].first);
                          Serial.print("    ---> ");
                          Serial.println(leaderBoards[gameKey][j].second);
                      }
                  }
#endif
              }
          } else {  // if the unit is not connected to wifi, just add the score locally
                maxScores[playedGame] = score;
          }
      }

}

void Scores::init() {

    //if the unit is connected to wifi, update the leaderboard with the values from the database
    if(GlobalStates::wifiIsConnected) {
        //set all the current scores
        getLeaderboardFromDatabase();

        //fill the local map with lowest score on the leaderboard
        for (auto &game: GlobalStates::gameList) {
            uint32_t playedGame = game->getFlagName();
            maxScores.emplace(playedGame, leaderBoards[playedGame][4].second);
        }
    }else {  // is the unit is not connected to wifi, init everything to 0
    //fill the local scores with 0
    for(auto &game:GlobalStates::gameList){
       uint32_t playedGame = game->getFlagName();
       maxScores.emplace(playedGame,0);}
    }


}

void Scores::getLeaderboardFromDatabase() {
    dataTransmit.getDataToHighscore(leaderBoards);

#ifdef DEBUG
    Serial.print("PRINTING LEADERBOARD:");
    for (int i = 0; i < GlobalStates::numberOfGameStates; i++){
        uint32_t gameKey = GlobalStates::gameList[i]->getFlagName();
        Serial.println(" ");
        for(int j = 0; j < 5; j++){
            Serial.print(leaderBoards[gameKey][j].first);
            Serial.print("    ---> ");
            Serial.println(leaderBoards[gameKey][j].second);
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
    dataTransmit.sendHighscoreToData(leaderBoards);
    return true;
}
