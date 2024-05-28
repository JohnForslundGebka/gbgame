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
  auto& info = *(currentChallenge->info);  // Dereference the pointer to get the JsonDocument
  String game = info["game"].as<String>();
  info["player2"] = wifi.userName;
  challengeIsRunning = true;

  if (game=="measury"){
    State::stateFlags.set(INDEX_DISTANCE_GAME);
  } else if(game=="voicy")
  {
      State::stateFlags.set(INDEX_MIC_GAME);
  }

}
