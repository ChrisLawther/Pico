#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "servo.h"

class ServoController {

public:
    ServoController() { }

    Servo *servo(int pin);
private:
    uint configuredSlices = 0;
};
