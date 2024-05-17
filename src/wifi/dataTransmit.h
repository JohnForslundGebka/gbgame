#ifndef GBGAME_DATATRANSMIT_H
#define GBGAME_DATATRANSMIT_H
#include "Firebase_Arduino_WiFiNINA.h"
#include <WiFiNINA.h>
#include "core/settings.h"
#include "states/globalStates.h"
#include <ArduinoJson.h>
#include <unordered_map>
#include <array>

#define DATABASE_URL "gbgame-6141c-default-rtdb.europe-west1.firebasedatabase.app"
#define DATABASE_SECRET "H3qt9cWGqH7hSVSP5lnuxj8VG1rPNpNj4xKWv3Wf"

class DataTransmit {
public:
    static DataTransmit& getInstance(); // Static method to access the instance

    // Delete copy constructor and assignment operator
    DataTransmit(const DataTransmit&) = delete;
    DataTransmit& operator=(const DataTransmit&) = delete;
    bool init();

    // Define the type for the leaderboard entry
    using LeaderboardEntry = std::pair<String, int>;
    // Define the type for the scores array, containing 5 top scores
    using ScoresArray = std::array<LeaderboardEntry, 5>;

    void getDataToHighscore(std::unordered_map<uint32_t, ScoresArray> leaderBoards);

    FirebaseData fbdo;

private:
    DataTransmit();  // Private constructor
    ~DataTransmit(); // Private destructor if needed
};

#endif //GBGAME_DATATRANSMIT_H
