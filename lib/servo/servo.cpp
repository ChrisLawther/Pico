#include <stdint.h>
#include "servo.h"

#ifdef TESTING
uint lastSlice = 0;
uint lastChannel = 0;
uint16_t lastValue = 0;

void pwm_set_chan_level(uint slice, uint channel, uint16_t value) {
    lastSlice = slice;
    lastChannel = channel;
    lastValue = value;
}

#endif

typedef void (*PwmLevelSetter)(uint, uint, uint16_t);

Servo::Servo(uint slice, uint channel, PwmLevelSetter set_func) {
    this->slice = slice;
    this->channel = channel;
    this->set_pwm = set_func;
}

// 0...1
void Servo::setValue(float value) {
    last_written_value = value;
    set_pwm(this->slice, this->channel, (uint16_t)(m * value + c));
}

// 0...180
void Servo::setAngle(float angle) {
    setValue(angle / 180.0);
}

// Expand the range from the usual 1...2ms
void Servo::setRange(uint from_us, uint to_us) {
    if ((from_us < 750) || (to_us > 2250) || (from_us >= to_us)) {
        // Don't like the range. Ignore it
        return;
    }

    // Calculate new m and c
    m = (to_us - from_us) * 65536 / 20000;
    c = from_us * 65536 / 20000;

    // Recalculate and send the value, given the new range
    setValue(last_written_value);
}

