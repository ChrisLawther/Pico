#ifndef _mpu6050_h_
#define _mpu6050_h_

#include "hardware/i2c.h"

enum AccelerationRange {
    twoG, fourG, eightG, sixteenG
};

enum GyroRange {
    twoHundredAndFiftyDegreesPerSecond,
    fiveHundredDegreesPerSecond,
    oneThousandDegreesPerSecond
};

typedef struct int16_vector3 {
    int16_t x;
    int16_t y;
    int16_t z;
} int16vector3_t;

typedef struct float_vector3 {
    float x;
    float y;
    float z;
} float_vector3_t;


class MPU6050 {
public:
    MPU6050(i2c_inst_t *i2c=i2c0, int gyroAddr = 0x68);
    void reset() const;
    bool checkId() const;

    void read(float_vector3 *accelerations, float_vector3 *rotations, float *temp) const;
    void setAccelerometerRange(AccelerationRange range);
    void setGyroRange(GyroRange range);

private:
    void read_raw(int16_vector3 *rawAccelerations, int16_vector3 *rawRotations, int16_t *rawTemp) const;

    i2c_inst_t *i2c;
    int gyroAddr;
    AccelerationRange accelerationRange;
    GyroRange gyroRange;
};

#endif
