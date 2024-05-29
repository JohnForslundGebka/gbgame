#include "challenge.h"
#include <ArduinoJson.h>


Challenge::Challenge(const String &id, const String &game, bool played, const String &player1Name, int player1Score) :
m_ID(id), m_game(game), m_played(played), m_player1Name(player1Name),
m_player1Score(player1Score){

    m_winner = "none";
    m_challengeSummery = game + "  -  " + m_player1Name;
}

String Challenge::getJsonData() const {
    JsonDocument doc;
    //convert to json Object
    JsonObject challenge = doc.to<JsonObject>();
    doc["game"] = m_game;
    doc["played"] = m_played;
    doc["player1"]["name"] = m_player1Name;
    doc["player1"]["score"] = m_player1Score;
    doc["player2"]["name"] = m_player2Name;
    doc["player2"]["score"] = m_player2Score;
    doc["winner"] = m_winner;

    // Serialize the JsonDocument to a String
    String jsonData;
    serializeJson(doc, jsonData);

    return jsonData;
}
