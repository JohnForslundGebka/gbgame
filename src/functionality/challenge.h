#ifndef GBGAME_CHALLENGE_H
#define GBGAME_CHALLENGE_H
#include <Arduino.h>

class Challenge {
    public:


//these values are filled when a challenge is downloaded from the database
    String m_ID{};
    String m_game{};
    bool m_played{};
    String m_player1Name{};
    int m_player1Score{};

    //these values are filled when a challenge is done
    String m_player2Name{};
    int m_player2Score{};
    String m_winner{};

    // Constructor for a challenge with only player 1 data
    Challenge(const String &id, const String &game, bool played, const String &player1Name, int player1Score);

    // Constructor for a completed challenge
    Challenge(const String &id, const String &game, bool played, const String &player1Name, int player1Score,
              const String &player2Name, int player2Score, const String &winner);


    String m_challengeSummery{};

    String getJsonData() const;
private:

};

#endif //GBGAME_CHALLENGE_H
