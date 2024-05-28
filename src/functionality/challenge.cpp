#include "challenge.h"

Challenge::Challenge(const String &id, JsonObject _info) : ID(id), info(_info) {
    String player1Name = info["player1"]["name"].as<String>();
    String game = info["game"].as<String>();
    challengeSummery = player1Name + "  -  " + game;
}
