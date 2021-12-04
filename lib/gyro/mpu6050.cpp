#include "mpu6050.h"

#include "hardware/gpio.h"      // GPIO_FUNC_I2C


MPU6050::MPU6050(i2c_inst_t *i2c, int gyroAddr)
:   i2c(i2c),
    gyroAddr(gyroAddr),
    gyroRange(twoHundredAndFiftyDegreesPerSecond),
    accelerationRange(twoG)
{
    i2c_init(i2c, 400 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);
}

void MPU6050::reset() const {
    uint8_t buf[] = { 0x6b, 0x00 };
    i2c_write_blocking(this->i2c, gyroAddr, buf, 2, false);
}

bool MPU6050::checkId() const {
    uint8_t buf[] = { 0x75 };
    uint8_t id = 0xff;

    i2c_write_blocking(this->i2c, gyroAddr, buf, 1, true);
    i2c_read_blocking(this->i2c, gyroAddr, &id, 1, false);

    return id == 0x68;
}

void MPU6050::setAccelerometerRange(AccelerationRange range) {
    uint8_t buf[] = { 0x1c, (uint8_t)(range << 3) };
    i2c_write_blocking(this->i2c, gyroAddr, buf, 2, true);
    accelerationRange = range;
}

void MPU6050::setGyroRange(GyroRange range) {
    uint8_t buf[] = { 0x1b, (uint8_t)(range << 3) };
    i2c_write_blocking(this->i2c, gyroAddr, buf, 2, true);
    gyroRange = range;
}

void MPU6050::read(float_vector3 *accelerations, float_vector3 *rotations, float *temp) const {
    int16vector3_t rawAccel, rawGyro;
    int16_t rawTemp;

    read_raw(&rawAccel, &rawGyro, &rawTemp);

    float accel_scale = (float)(16384 >> accelerationRange);

    accelerations->x = (float)rawAccel.x / accel_scale;
    accelerations->y = (float)rawAccel.y / accel_scale;
    accelerations->z = (float)rawAccel.z / accel_scale;

    float gyro_scale = 131.0 / (float)gyroRange;

    rotations->x = (float)rawGyro.x / gyro_scale;
    rotations->y = (float)rawGyro.y / gyro_scale;
    rotations->z = (float)rawGyro.z / gyro_scale;

    *temp = (rawTemp / 340.0) + 36.53;
}

void MPU6050::read_raw(int16_vector3 *rawAccelerations, int16_vector3 *rawRotations, int16_t *rawTemp) const {
    uint8_t buffer[14];

    // 6 bytes from 0x3b for acceleration
    // 2 bytes of temperature from 0x41;
    // 6 bytes from 0x43 for gyro

    uint8_t val = 0x3b;
    i2c_write_blocking(this->i2c, gyroAddr, &val, 1, true);  // keep master
    i2c_read_blocking(this->i2c, gyroAddr, buffer, 14, false);

    rawAccelerations->x = buffer[0] << 8 | buffer[1];
    rawAccelerations->y = buffer[2] << 8 | buffer[1];
    rawAccelerations->z = buffer[4] << 8 | buffer[5];

    *rawTemp = buffer[6] << 8 | buffer[7];

    rawRotations->x =  buffer[8] << 8 | buffer[9];
    rawRotations->y =  buffer[10] << 8 | buffer[11];
    rawRotations->z =  buffer[12] << 8 | buffer[13];
}
