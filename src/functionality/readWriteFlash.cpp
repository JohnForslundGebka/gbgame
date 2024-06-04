#include "readWriteFlash.h"
#include <kvstore_global_api.h>
#include <mbed_error.h>
#include "rtos.h"
#include "mbed.h"
#include <cstring>

namespace flash {

    bool writeToFlash(const std::string& inputText, const char *key) {
        // Write data to the store.
        const char *value = inputText.c_str();
        size_t valueSize = inputText.size();  // Corrected to store the size of the string data

        int result = kv_set(key, value, valueSize, 0);
        if (result != MBED_SUCCESS) {
            Serial.print("kv_set failed with error code ");
            Serial.println(result);
            return false;
        }
        return true;
    }

    char* readFromFlash(const char *key) {
        // Read data from the store.
        kv_info_t infoBuffer;

        int result = kv_get_info(key, &infoBuffer);
        if (result != MBED_SUCCESS) {
            Serial.print("kv_get_info failed with error code ");
            Serial.println(result);
            while (true) {}  // Halt execution, consider proper error handling
        }

        char* readBuffer = new char[infoBuffer.size + 1]; // Allocate memory to hold the read data plus a null terminator
        memset(readBuffer, 0, infoBuffer.size + 1);  // Initialize the buffer to zero

        result = kv_get(key, readBuffer, infoBuffer.size, nullptr);
        if (result != MBED_SUCCESS) {
            Serial.print("kv_get failed with error code ");
            Serial.println(result);
            delete[] readBuffer;  // Free memory if read fails
            while (true) {}  // Halt execution, consider proper error handling
        }

        return readBuffer;
    }
}
