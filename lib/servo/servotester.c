#include "servo.h"
#include <stdio.h>

// Build using:
//    g++ -DTESTING Servo.cpp servotester.c -o servoTest
//
// Serves as a crude way of seeing what values would have been written to the hardware.

int main(int argc, char *argv[]) {

    Servo s(0,0);

    s.setValue(0);
    printf("Slice: %d  Channel: %d  Value: 0x%04d\n", lastSlice, lastChannel, lastValue);

    s.setValue(1);
    printf("Slice: %d  Channel: %d  Value: 0x%04d\n", lastSlice, lastChannel, lastValue);

    s.setAngle(0);
    printf("Slice: %d  Channel: %d  Value: 0x%04d\n", lastSlice, lastChannel, lastValue);

    s.setAngle(180);
    printf("Slice: %d  Channel: %d  Value: 0x%04d\n", lastSlice, lastChannel, lastValue);

    s.setRange(750, 2250);
    s.setValue(0);
    printf("Slice: %d  Channel: %d  Value: 0x%04d\n", lastSlice, lastChannel, lastValue);

    s.setValue(1);
    printf("Slice: %d  Channel: %d  Value: 0x%04d\n", lastSlice, lastChannel, lastValue);

    s.setAngle(0);
    printf("Slice: %d  Channel: %d  Value: 0x%04d\n", lastSlice, lastChannel, lastValue);

    s.setAngle(180);
    printf("Slice: %d  Channel: %d  Value: 0x%04d\n", lastSlice, lastChannel, lastValue);

    return 0;
}
