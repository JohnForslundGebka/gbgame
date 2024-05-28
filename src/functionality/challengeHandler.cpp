#include "challengeHandler.h"

ChallengeHandler &ChallengeHandler::getInstance() {
    static ChallengeHandler instance;
    return instance;
}

ChallengeHandler::ChallengeHandler() {

}
