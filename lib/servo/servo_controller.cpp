#include "servo_controller.h"

Servo *ServoController::servo(int pin) {
    // Configure the pin
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Get the PWM slice (1 of 8) and channel (A or B) for the pin
    uint slice = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);

    // Configure 50Hz
    if ((configuredSlices & (1<<slice)) == 0) {
        // Get the default configuration
        pwm_config config = pwm_get_default_config();

        // Set the clock divider to get us close to 50Hz at maximum resolution
        pwm_config_set_clkdiv_int(&config, 38);
        pwm_init(slice, &config, true);
        pwm_set_wrap(slice, 0xffff);

        // Enable the slice
        pwm_set_enabled(slice, true);

        // ... and remember that it's configured/enabled
        configuredSlices |= (1<<slice);
    }

    return new Servo(slice, channel);
}
