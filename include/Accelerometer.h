#pragma once 

#include "i2c.h"
#include "ioMapping.h"

#define MPU6050_ADDR         0x68
#define MPU6050_PWR_MGMT_1   0x6B
#define MPU6050_ACCEL_XOUT_H 0x3B

class Accelerometer {
private:
    i2c* i2c_bus;
    int16_t xAccel, yAccel, zAccel;

public:
    Accelerometer(uint8_t sda, uint8_t scl, i2c_port_t port);

    void begin();

    void readRawAccel();

    int16_t getXAccel();
    int16_t getYAccel();
    int16_t getZAccel();
};
