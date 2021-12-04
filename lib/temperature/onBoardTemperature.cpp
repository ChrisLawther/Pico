#include "onBoardTemperature.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

float toDegrees(float input);

// 12-bit ADC value to volts
const float conversion_factor = 3.3f / (1<<12);

void OnBoardTemperature::enable() {
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

float OnBoardTemperature::read() {
    uint16_t value = adc_read();
    float volts = value * conversion_factor;
    float degrees = toDegrees(volts);

    // printf("%d (%5.4fv) -> %5.2f°C\n", value, volts, degrees);
    return degrees;
};

// Volts to degrees centigrade
float toDegrees(float input) {
    return 27 - (input - 0.706) / 0.001721;
}
