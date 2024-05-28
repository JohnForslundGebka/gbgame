#ifndef GBGAME_CHALLENGEHANDLER_H
#define GBGAME_CHALLENGEHANDLER_H


class ChallengeHandler {
public:
    static ChallengeHandler& getInstance(); // Static method to access the instance
    // Delete copy constructor and assignment operator for singleton class
    ChallengeHandler(const ChallengeHandler&) = delete;
    ChallengeHandler& operator=(const ChallengeHandler&) = delete;
private:
    ChallengeHandler();  // Private constructor
};


#endif //GBGAME_CHALLENGEHANDLER_H
