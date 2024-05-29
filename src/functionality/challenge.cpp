#include "challenge.h"


Challenge::Challenge(const String &id, const String &game, bool played, const String &player1Name, int player1Score) :
m_ID(id), m_game(game), m_played(played), m_player1Name(player1Name),
m_player1Score(player1Score){

    m_winner = "none";
    m_challengeSummery = game + "  -  " + m_player1Name;
}
