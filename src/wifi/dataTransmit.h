/**
 * @class DataTransmit
 * @brief is responsible for setting up and managing the wifi connection
 *
 *
 */
#ifndef GBGAME_DATATRANSMIT_H
#define GBGAME_DATATRANSMIT_H
#include "Firebase_Arduino_WiFiNINA.h"
#include <WiFiNINA.h>
#include "core/settings.h"
#include "core/macros.h"
#include "functionality/challenge.h"
#include "states/globalStates.h"
#include <ArduinoJson.h>
#include <unordered_map>
#include <array>
#include <vector>

class DataTransmit {
public:
    static DataTransmit& getInstance(); // Static method to access the instance

    // Delete copy constructor and assignment operator for singleton class
    DataTransmit(const DataTransmit&) = delete;
    DataTransmit& operator=(const DataTransmit&) = delete;
    bool init(); //This function connects the arduino to Wi-Fi. Will return true if connection was successful
    bool wifiIsConnected = false; //flag that is used to change how tod highscore is loaded

    // Define the type for the leaderboard entry
    using LeaderboardEntry = std::pair<String, int>;
    // Define the type for the scores array, containing 5 top scores
    using ScoresArray = std::array<LeaderboardEntry, 5>;

    //updates the local leaderboard with the values from the firebase database
    void getDataToHighscore(std::unordered_map<uint32_t, ScoresArray> &leaderBoards);

    //will take the local leaderboard and upload it to the airbase database
    void sendHighscoreToData(std::unordered_map<uint32_t, ScoresArray> &leaderBoards);
    //will take the local challenge and upload it to the airbase database
    void sendChallengeToData(const String& challenge);

    void endChallengeToData(String ID, String challengeData);
    //function for getting the wifi-networks
    void getNetworkNames(std::vector<String> &networkList);
    //updates the local challenges with the values from the firebase database
    void getChallengesFromData(std::vector<Challenge> &challenges);

    //class that handles the connecting to the Firebase database
    FirebaseData fbdo;

    String userName;
    char* ssid;
    char* password;
private:
    DataTransmit();  // Private constructor
    ~DataTransmit(); // Private destructor
};
#endif //GBGAME_DATATRANSMIT_H
