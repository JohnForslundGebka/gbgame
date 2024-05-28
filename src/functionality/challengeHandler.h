#ifndef GBGAME_CHALLENGEHANDLER_H
#define GBGAME_CHALLENGEHANDLER_H
#include <ArduinoJson.h>
#include "wifi/dataTransmit.h"

class Challenge;


class ChallengeHandler {
public:

    static ChallengeHandler& getInstance(); // Static method to access the instance
    // Delete copy constructor and assignment operator for singleton class
    ChallengeHandler(const ChallengeHandler&) = delete;
    ChallengeHandler& operator=(const ChallengeHandler&) = delete;
    Challenge* currentChallenge;

    void startChallenge(Challenge* c);
    bool endChallenge();

    DataTransmit &wifi = DataTransmit::getInstance();
    bool challengeIsRunning = false;
private:
    ChallengeHandler();  // Private constructor
};


#endif //GBGAME_CHALLENGEHANDLER_H
