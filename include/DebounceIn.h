#ifndef GBGAME_DEBOUNCEIN_H
#define GBGAME_DEBOUNCEIN_H

#include "mbed.h"
#include "rtos.h"
#include <chrono>

using namespace std::chrono;
using namespace mbed;
using namespace rtos;


#define DEFAULT_DEBOUNCE 20ms

class DebounceIn {
public:
    typedef enum {
        None = 0,
        Rise,
        Fall
    } Type;

    DebounceIn(PinName pin, PinMode mode = PullNone);
    void rise(Callback<void()> cb, microseconds timeout = DEFAULT_DEBOUNCE);
    void fall(Callback<void()> cb, microseconds timeout = DEFAULT_DEBOUNCE);
    int32_t read();

    operator int();

private:
    InterruptIn _interrupt;
    Timeout _timeout[2];
    Callback<void()> _cb[2];
    void intRiseCb();
    void intFallCb();
    void timeoutRiseCb();
    void timeoutFallCb();
    microseconds _timeout_interval[2];
};
#endif //GBGAME_DEBOUNCEIN_H
