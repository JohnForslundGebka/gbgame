#ifndef GBGAME_DATATRANSMIT_H
#define GBGAME_DATATRANSMIT_H
#include "Firebase_Arduino_WiFiNINA.h"
#include <WiFiNINA.h>
#include "core/settings.h"

#define DATABASE_URL "gbgame-6141c-default-rtdb.europe-west1.firebasedatabase.app"
#define DATABASE_SECRET "H3qt9cWGqH7hSVSP5lnuxj8VG1rPNpNj4xKWv3Wf"

class DataTransmit {
public:
    static DataTransmit& getInstance(); // Static method to access the instance

    // Delete copy constructor and assignment operator
    DataTransmit(const DataTransmit&) = delete;
    DataTransmit& operator=(const DataTransmit&) = delete;

    bool init();

    FirebaseData fbdo;

private:
    DataTransmit();  // Private constructor
    ~DataTransmit(); // Private destructor if needed
};

#endif //GBGAME_DATATRANSMIT_H
