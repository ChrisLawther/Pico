# Servo controller

Provides an interface to allow the PWM hardware to be configured to generate
signals suitable for hobby-grade servos

# Building

Once per session:

    export PICO_SDK_PATH=../../pico-sdk

(TODO: Add that to .bashrc or something)

To mount / copy / unmount the pico

    sudo mount /dev/sda1 pico
    sudo cp ServoController.uf2 pico/
    sudo umount pico
