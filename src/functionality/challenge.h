#ifndef GBGAME_CHALLENGE_H
#define GBGAME_CHALLENGE_H
#include <ArduinoJson.h>

class Challenge {
    public:
    String ID{};
    JsonObject info;
    Challenge(const String &id, JsonObject _info);
    String challengeSummery{};
};

#endif //GBGAME_CHALLENGE_H
