#include "challengeHandler.h"
#include "challenge.h"
#include "core/state.h"



ChallengeHandler &ChallengeHandler::getInstance() {
    static ChallengeHandler instance;
    return instance;
}

ChallengeHandler::ChallengeHandler() {
}

void ChallengeHandler::respondToChallenge(Challenge* challenge) {


  currentChallenge = challenge;
  String game = currentChallenge->m_game;
  currentChallenge->m_player2Name = wifi.userName;

  respondingToChallenge = true;

  if (game=="Measury"){
      State::stateFlags.set(GlobalStates::stateList[INDEX_DISTANCE_GAME]->getFlagName());
  } else if(game=="Voicy")
  {
      State::stateFlags.set(GlobalStates::stateList[INDEX_MIC_GAME]->getFlagName());
  }
}

bool ChallengeHandler::endResponseToChallenge(int player2Score) {

    respondingToChallenge = false;

    String player1Name = currentChallenge->m_player1Name;
    int player1Score = currentChallenge->m_player1Score;

    //adding player2 score to the challenge
    currentChallenge->m_player2Score = player2Score;

    currentChallenge->m_played = true;

    //set the winning players name
    bool challengeWasWon = (player2Score > player1Score);
    (challengeWasWon) ? currentChallenge->m_winner = wifi.userName : currentChallenge->m_winner = player1Name;

    //send the new data to the database
    String jsonData = currentChallenge->getJsonData();
    String ID = currentChallenge->m_ID;

    Serial.println("JSON data to send: " + jsonData);
    Serial.println(" ");
    Serial.println("CHALLENGE ID IS:  " + ID);

    wifi.endChallengeToData(ID,jsonData);

    currentChallenge = nullptr;
    return challengeWasWon;
}

void ChallengeHandler::startChallenge(int gameIndex) {
    startingAChallenge = true;
    State::stateFlags.set(GlobalStates::stateList[gameIndex]->getFlagName());
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

    Serial.println("WE SENT A CHALLENGE");
    //Go to some menu or something
    State::stateFlags.set(GlobalStates::stateList[INDEX_MULTIPLAYER_MENU]->getFlagName());
}

void ChallengeHandler::getChallengesFromLobby(std::vector<Challenge*> &lobbyList) {
    challenges.clear();
    lobbyList.clear();
    wifi.getChallengesFromData(challenges);
    //add challenges to lobbylist
    for (auto &challenge: challenges) {
        if (!challenge.m_played && challenge.m_player1Name != wifi.userName) {
            lobbyList.push_back(&challenge);
        }
    }
}