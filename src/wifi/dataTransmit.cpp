#include "dataTransmit.h"

DataTransmit::DataTransmit() {
    // Constructor code here
}

DataTransmit::~DataTransmit() {
    // Destructor code here, if needed
}

DataTransmit& DataTransmit::getInstance() {
    static DataTransmit instance; // Guaranteed to be destroyed and instantiated on first use.
    return instance;
}

bool DataTransmit::init() {

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

    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(GlobalSettings::ssid, GlobalSettings::password);
        Serial.print(".");
        delay(5000);  // Wait 5 seconds before retrying
    }

    Firebase.begin(DATABASE_URL, DATABASE_SECRET,GlobalSettings::ssid,GlobalSettings::password);
    Firebase.reconnectWiFi(true);

    return (WiFi.status() == WL_CONNECTED);

#ifdef DEBUG
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    delay(1000);
#endif
}
