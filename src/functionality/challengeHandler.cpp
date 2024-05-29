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

void ChallengeHandler::respondToChallenge(int numberOfChallengeInVector) {
  currentChallenge = &challenges[numberOfChallengeInVector];
  String game = currentChallenge->m_game;

  respondingToChallenge = true;

  if (game=="measury"){
    State::stateFlags.set(INDEX_DISTANCE_GAME);
  } else if(game=="voicy")
  {
      State::stateFlags.set(INDEX_MIC_GAME);
  }
}

bool ChallengeHandler::endResponseToChallenge(int player2Score) {

    respondingToChallenge = false;

    String player1Name = currentChallenge->m_player1Name;
    //adding player2 score to the challenge
    currentChallenge->m_player2Name = wifi.userName;
    currentChallenge->m_player2Score = player2Score;

    int player1Score = currentChallenge->m_player1Score;
    currentChallenge->m_played = true;

    //set the winning players name
    bool challengeWasWon = (player2Score > player1Score);
    (challengeWasWon) ? currentChallenge->m_winner = player1Name : currentChallenge->m_winner = wifi.userName;

    //send the new data to the database
    String jsonData = currentChallenge->getJsonData();
    String ID = currentChallenge->m_ID;
    wifi.endChallengeToData(ID,jsonData);

    currentChallenge = nullptr;
    return challengeWasWon;
}

void ChallengeHandler::startChallenge(const String& game) {
    startingAChallenge = true;
    if (game=="measury"){
        State::stateFlags.set(INDEX_DISTANCE_GAME);
    } else if(game=="voicy")
    {
        State::stateFlags.set(INDEX_MIC_GAME);
    }
}

void ChallengeHandler::endStartChallenge(State *state, int score) {

    String gameName = state->m_stateName;
    //create the challenge object
    JsonDocument doc;
    //convert to json Object
    JsonObject challenge = doc.to<JsonObject>();
    //fill with data
    challenge["game"] = gameName;
    challenge["played"] = false;
    challenge["player1"]["name"] = wifi.userName;
    challenge["player1"]["score"] = score;
    challenge["winner"] = "none";

    // Serialize JSON to String (to send to the database)
    String output;
    serializeJson(doc, output);
    startingAChallenge = false;

    wifi.sendChallengeToData(output);

    //gå tillbaks till någon meny eller något

}

void ChallengeHandler::getChallengesFromLobby(std::vector<String> &lobbyList) {
    challenges.clear();
    lobbyList.clear();
    wifi.getChallengesFromData(challenges);
    //add challenges to lobbylist
    for (auto &challenge: challenges) {
        lobbyList.push_back(challenge.m_challengeSummery);
    }
}