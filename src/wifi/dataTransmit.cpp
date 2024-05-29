
#include "dataTransmit.h"
#include "core/state.h"
#include "functionality/challenge.h"



DataTransmit::DataTransmit() {

}

DataTransmit::~DataTransmit() {

}

DataTransmit& DataTransmit::getInstance() {
    static DataTransmit instance; // Guaranteed to be destroyed and instantiated on first use.
    return instance;
}

bool DataTransmit::init() {
    using namespace std::chrono;

#ifdef DEBUG
    Serial.println("Attempting to connect to WiFi network...");
    int n = WiFi.scanNetworks();
    Serial.println("Scan complete:");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(" dBm) ");
            Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
            delay(10);
        }
    }
#endif
   int wifiTries = 0;
    Serial.println(userName);
    Serial.println(ssid);
    Serial.println(password);
    while (WiFi.status() != WL_CONNECTED ) {
        WiFi.begin(ssid, password);
        Serial.print(".");
        rtos::ThisThread::sleep_for(std::chrono::seconds(3));  // Wait 3 seconds before retrying
        if (wifiTries == 6){
            Serial.println("CONNECTION BAD");
            return false;
        } else {
            wifiTries++;
        }
    }



    Firebase.begin(DATABASE_URL, DATABASE_SECRET,ssid,password);
    Firebase.reconnectWiFi(true);
    wifiIsConnected = true;
    Serial.println("CONNECTION GOOD");
    return (WiFi.status() == WL_CONNECTED);

#ifdef DEBUG
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    delay(1000);
#endif
}

void DataTransmit::getDataToHighscore(std::unordered_map<uint32_t, ScoresArray> &leaderBoards){

    //Do this for all the games in our gamestate list
        for (const auto & i : GlobalStates::gameList) {
            uint32_t gameKey = i->getFlagName();
            String gameName = i->m_stateName;
            String basePath = "/Leaderbord/" + gameName;  // Path to the leaderboard data in Firebase

            for (int j = 0; j < 5; j++) {
                String fullPath = basePath + "/score_" + static_cast<String>(j + 1);

                if (Firebase.getJSON(fbdo, fullPath)) {
                    if (fbdo.dataType() == "json") {
                        // Use JsonDocument
                        JsonDocument doc;
                        DeserializationError error = deserializeJson(doc, fbdo.jsonData());
                        if (!error) {

                            String name = doc["name"].as<String>();
                            int score = doc["score"].as<int>();
                            leaderBoards[gameKey][j] = std::make_pair(name, score);
                        } else {
                            Serial.print("deserializeJson() failed with code ");
                            Serial.println(error.c_str());
                        }
                    }
                } else {
                    Serial.println("Failed to fetch data: " + fbdo.errorReason());
                }
            }
        }

}

void DataTransmit::sendHighscoreToData(std::unordered_map<uint32_t, ScoresArray> &leaderBoards) {

    //Do this for all the games in our gamestate list
    for (int i = 0; i < GlobalStates::numberOfGameStates; i++){
        uint32_t gameKey = GlobalStates::gameList[i]->getFlagName();
        String gameName = GlobalStates::gameList[i]->m_stateName;
        String basePath = "/Leaderbord/" + gameName;  // Path to the leaderboard data in Firebase

        //double check to see if the game has a highscore
        if (leaderBoards.find(gameKey) != leaderBoards.end()) {
            Serial.println("sending data to DB");

            for (int j = 0; j < 5; j++) {
                String fullPath = basePath + "/score_" + String(j + 1);
                JsonDocument doc;

                doc["name"] = leaderBoards[gameKey][j].first;
                doc["score"] = leaderBoards[gameKey][j].second;

                // Serialize JSON to a string
                String jsonData;
                serializeJson(doc, jsonData);
                Serial.println(jsonData);

                if (!Firebase.setJSON(fbdo, fullPath, jsonData)) {
                    Serial.println("Failed to send data: " + fbdo.errorReason());
                }
            }
        } else{
            Serial.println("No data for that game");
        }
    }
}

void DataTransmit::getNetworkNames(std::vector<String> &networkList) {

    networkList.clear();
    int n = WiFi.scanNetworks();
    if (n == 0){
        networkList.push_back("NO NETWORKS FOUND");
        return;
    }
    for (int i = 0; i < n; ++i) {
        networkList.emplace_back(WiFi.SSID(i));
        Serial.println(WiFi.SSID(i));
        delay(10);
    }
}

void DataTransmit::getChallengesFromData(std::vector<Challenge> &challenges) {
   fbdo.clear();
   String path = "/Lobby";

   if (Firebase.getJSON(fbdo, path)) {
       JsonDocument doc;
       DeserializationError error = deserializeJson(doc, fbdo.jsonData());
       if (error) {
           Serial.print("deserializeJson() failed: ");
           Serial.println(error.c_str());
           return;
       }
       JsonObject obj = doc.as<JsonObject>();
       for (JsonPair p : obj){   //create the challenge objects and put them into the vector
           String ID = p.key().c_str();
           JsonObject challengeInfo = p.value().as<JsonObject>();
           // Extract each field from the JsonObject
           String game = challengeInfo["game"].as<String>();
           bool played = challengeInfo["played"].as<bool>();
           String player1Name = challengeInfo["player1"]["name"].as<String>();
           int player1Score = challengeInfo["player1"]["score"].as<int>();

            challenges.emplace_back(ID,game,played,player1Name,player1Score);
       }
   }

}

void DataTransmit::sendChallengeToData(const String& challenge) {

    String path = "/Lobby";
    if (Firebase.pushJSON(fbdo, path, challenge)) {
        Serial.println("Challenge added successfully.");
        Serial.println("Generated Challenge ID: " + fbdo.pushName());  // Firebase generates a unique push ID
    } else {
        Serial.print("Failed to add challenge: ");
        Serial.println(fbdo.errorReason());
    }

}

void DataTransmit::endChallengeToData(String ID, String challengeData) {

}
