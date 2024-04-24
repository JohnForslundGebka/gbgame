#include "DebounceIn.h"
#include "mbed.h"

using namespace mbed;
using namespace rtos;


DebounceIn::DebounceIn(PinName pin, PinMode mode) :
        _interrupt(pin, mode) {
    _cb[0] = NULL;
    _cb[1] = NULL;
}

void DebounceIn::rise(Callback<void()> cb, microseconds timeout) {
    if (cb) {
        _cb[0] = cb;
        _timeout_interval[0] = timeout;
        _interrupt.rise(callback(this, &DebounceIn::intRiseCb));

    } else {
        _cb[0] = NULL;
        _interrupt.rise(NULL);
        _timeout[0].detach();
    }
}

void DebounceIn::fall(Callback<void()> cb, microseconds timeout) {
    if (cb) {
        _cb[1] = cb;
        _timeout_interval[1] = timeout;
        _interrupt.fall(callback(this, &DebounceIn::intFallCb));

    } else {
        _cb[1] = NULL;
        _interrupt.fall(NULL);
        _timeout[1].detach();
    }
}

void DebounceIn::timeoutRiseCb() {
    if (read()) {
        if (_cb[0]) {
            _cb[0].call();
        }
    }

    _interrupt.rise(callback(this, &DebounceIn::intRiseCb));
}

void DebounceIn::intRiseCb() {
    _timeout[0].attach(callback(this, &DebounceIn::timeoutRiseCb), _timeout_interval[0]);
    _interrupt.rise(NULL);  // detach interrupt
}

void DebounceIn::timeoutFallCb() {
    if (!read()) {
        if (_cb[1]) {
            _cb[1].call();
        }
    }

    _interrupt.fall(callback(this, &DebounceIn::intFallCb));
}

void DebounceIn::intFallCb() {
    _timeout[1].attach(callback(this, &DebounceIn::timeoutFallCb), _timeout_interval[1]);
    _interrupt.fall(NULL);  // detach interrupt
}

int32_t DebounceIn::read() {
    return _interrupt.read();
}

DebounceIn::operator int() {
    return read();
}

