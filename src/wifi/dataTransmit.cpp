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