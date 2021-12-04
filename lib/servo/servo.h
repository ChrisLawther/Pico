#ifndef _SERVO_H_
#define _SERVO_H_

#ifndef TESTING
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#else
#include <stdint.h>
typedef unsigned int uint;

extern uint lastSlice;
extern uint lastChannel;
extern uint16_t lastValue;

void pwm_set_chan_level(uint slice, uint channel, uint16_t value);

#endif

typedef void (*PwmLevelSetter)(uint, uint, uint16_t);

class Servo {
public:
    Servo(uint slice, uint channel, PwmLevelSetter set_func = pwm_set_chan_level);

    // 0...1
    void setValue(float value);

    // 0...180
    void setAngle(float value);

    // Expand the range from the usual 1...2ms
    void setRange(uint from_us, uint to_us);

private:
    uint slice;
    uint channel;
    PwmLevelSetter set_pwm;

    float m = 65535.0 * 0.05;
    float c = 65535.0 * 0.05;

    float last_written_value = 0.0;
};

#endif
