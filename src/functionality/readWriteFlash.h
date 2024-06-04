#ifndef GBGAME_READWRITEFLASH_H
#define GBGAME_READWRITEFLASH_H

#include <Arduino.h>
#include <string>

namespace flash {
    bool writeToFlash(const std::string& inputText, const char *key);
    char* readFromFlash(const char *key);
}

#endif // GBGAME_READWRITEFLASH_H
