#ifndef GBGAME_CHALLENGE_H
#define GBGAME_CHALLENGE_H
#include <ArduinoJson.h>

class Challenge {
    public:
    String ID{};
    JsonDocument* info;
    Challenge(const String &id, JsonDocument *info);
};

#endif //GBGAME_CHALLENGE_H
