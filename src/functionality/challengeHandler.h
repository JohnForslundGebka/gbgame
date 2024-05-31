#ifndef GBGAME_CHALLENGEHANDLER_H
#define GBGAME_CHALLENGEHANDLER_H
#include <ArduinoJson.h>
#include "wifi/dataTransmit.h"
#include <vector>

class Challenge;
class State;

class ChallengeHandler {
public:
    static ChallengeHandler& getInstance(); // Static method to access the instance
    // Delete copy constructor and assignment operator for singleton class
    ChallengeHandler(const ChallengeHandler&) = delete;
    ChallengeHandler& operator=(const ChallengeHandler&) = delete;
    Challenge* currentChallenge;

    void startChallenge(int gameIndex);
    void endStartChallenge(State *state, int score);

    void respondToChallenge(Challenge* challenge);
    bool endResponseToChallenge(int score);
    void getChallengesFromLobby(std::vector<Challenge*> &lobbyList);

    DataTransmit &wifi = DataTransmit::getInstance();
    bool respondingToChallenge = false;
    bool startingAChallenge = false;
    std::vector<Challenge> challenges;
private:
    ChallengeHandler();  // Private constructor

};


#endif //GBGAME_CHALLENGEHANDLER_H
