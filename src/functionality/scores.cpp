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

bool Scores::addScore(int score,State *gameThatWasPlayed) {

    //get the flag of the game the was played
    uint32_t playedGame = gameThatWasPlayed->getFlagName();
      //if the user has set a new high score
      if(score > maxScores[playedGame]) {
       //if the unit is connected to Wi-Fi, try to add the score to the leaderboard
          if (dataTransmit.wifiIsConnected) {
              if (addScoreToLeaderboard(score, playedGame)) {
                  GlobalStates::newHighscore.setScore(score);
                  return true;
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
          } else {  // if the unit is not connected to Wi-Fi, just add the score locally
              addScoreToLeaderboard(score, playedGame);
              GlobalStates::newHighscore.setScore(score);
              return true;
          }
      } else{
          return false;
      }

}

void Scores::init() {

#ifdef DEBUG
    if(dataTransmit.wifiIsConnected)
    Serial.println("wifi is connected!!");
#endif

    //if the unit is connected to Wi-Fi, update the leaderboard with the values from the database
    if(dataTransmit.wifiIsConnected) {
        //set all the current scores
        getLeaderboardFromDatabase();

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
    //fill the map with temp values
        for (auto & game : GlobalStates::gameList){
            uint32_t gameKey = game->getFlagName();
            int score = 5;
            for (int j = 0; j < 5; j++){
                leaderBoards[gameKey][j] = std::make_pair("-", score);
                score--;
            }
        }

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

bool Scores::addScoreToLeaderboard(int score, uint32_t playedGame) {

    if(dataTransmit.wifiIsConnected){
    //update the leaderboard from Database
    getLeaderboardFromDatabase();
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
    // Insert the new score at the found position
    leaderBoards[playedGame][pos] = std::make_pair(GlobalSettings::userName, score);

    //make the 5th score the current highest score
    maxScores[playedGame] = leaderBoards[playedGame][4].second;
    if(dataTransmit.wifiIsConnected) {
        dataTransmit.sendHighscoreToData(leaderBoards);
    }
    return true;
}
