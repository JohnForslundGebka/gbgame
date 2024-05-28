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

void ChallengeHandler::startChallenge(Challenge *c) {
  currentChallenge = c;
  auto& info = *(currentChallenge->info);  // Dereference the pointer to get the JsonObject
  String game = info["game"].as<String>();

    JsonObject player2 = info["player2"].to<JsonObject>();

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
    auto& info = *(currentChallenge->info);  // Dereference the pointer to get the JsonDocument

    String player1Name = info["player2"]["name"].as<String>();
    //adding player2 score to a database
    info["player2"]["score"] = score;

    int player1Score = info["player1"]["score"].as<int>();

    bool challengeWasWon = (score > player1Score);
    (challengeWasWon) ? info["winner"] = player1Name : info["winner"] = wifi.userName;

    //funktion som updaterar challengedatabasen

    currentChallenge = nullptr;

    return challengeWasWon;
}
