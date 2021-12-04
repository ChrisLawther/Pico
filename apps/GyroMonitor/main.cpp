#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"

#include "onBoardTemperature.h"
#include "mpu6050.h"

// The one LED
const uint LED_PIN = 25;

#define I2C_PORT i2c0

int main() {
    stdio_init_all();
    printf("ADC onboard temperature monitor\n");

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    // Switch the LED on at least once
    gpio_put(LED_PIN, 1);

    OnBoardTemperature::enable();

    uint ledValue = 0;

    MPU6050 mpu6050 = MPU6050();

//     mpu6050_reset();
    mpu6050.reset();
    mpu6050.setAccelerometerRange(twoG);

    if (!mpu6050.checkId()) {
        return 0;
    }

    float_vector3_t acceleration, gyro;
    float temp;

    while (1) {
        ledValue = 1 - ledValue;
        gpio_put(LED_PIN, ledValue);
        // Gyro / acceleration
        mpu6050.read(&acceleration, &gyro, &temp);

        float onBoardTemp = OnBoardTemperature::read();

        printf("  Acc. X = %6.2f, Y= %6.2f, Z= %6.2f   Gyro X = %6.2f, Y= %6.2f, Z= %6.2f Temp= %5.2f°C (onBoard= %5.2f°C)\r",
            acceleration.x, acceleration.y, acceleration.z,
            gyro.x, gyro.y, gyro.z,
            temp,
            onBoardTemp
        );

        sleep_ms(100);
    }
}
