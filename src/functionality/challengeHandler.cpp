#include "challengeHandler.h"
#include "challenge.h"
#include "core/state.h"
#include "core/macros.h"


ChallengeHandler &ChallengeHandler::getInstance() {
    static ChallengeHandler instance;
    return instance;
}

ChallengeHandler::ChallengeHandler() {

}

void ChallengeHandler::startChallenge(int numberOfChallengeInVector) {
  currentChallenge = &challenges[numberOfChallengeInVector];
  String game = currentChallenge->info["game"].as<String>();

  JsonObject player2 = currentChallenge->info["player2"].to<JsonObject>();

  player2["name"] = wifi.userName;
  challengeIsRunning = true;

  if (game=="measury"){
    State::stateFlags.set(INDEX_DISTANCE_GAME);
  } else if(game=="voicy")
  {
      State::stateFlags.set(INDEX_MIC_GAME);
  }
}

bool ChallengeHandler::endChallenge(int score) {

    challengeIsRunning = false;
    String ID = currentChallenge->ID;

    String player1Name = currentChallenge->info["player2"]["name"].as<String>();
    //adding player2 score to a database
    currentChallenge->info["player2"]["score"] = score;

    int player1Score = currentChallenge->info["player1"]["score"].as<int>();
    currentChallenge->info["played"] = true;

    bool challengeWasWon = (score > player1Score);
    (challengeWasWon) ? currentChallenge->info["winner"] = player1Name : currentChallenge->info["winner"] = wifi.userName;

    //funktion som updaterar challengedatabasen

    currentChallenge = nullptr;
    return challengeWasWon;
}

void ChallengeHandler::getChallengesFromLobby(std::vector<String> &lobbyList) {
    challenges.clear();
    wifi.getChallengesFromData(challenges);
    //add challenges to lobbylist
    for (auto &challenge: challenges) {
        lobbyList.push_back(challenge.challengeSummery);
    }

}
