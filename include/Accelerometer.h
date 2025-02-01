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
    Accelerometer() {
        i2c_bus = new i2c(ioMapping::sda, ioMapping::scl, I2C_NUM_1);
    }

    void begin() {
        i2c_bus->writeByte(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0x00);  // Wake up MPU6050
    }

    void readRawAccel() {
        uint8_t buffer[6];
        i2c_bus->readBytes(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, buffer, 6);
        
        xAccel = (buffer[0] << 8) | buffer[1];
        yAccel = (buffer[2] << 8) | buffer[3];
        zAccel = (buffer[4] << 8) | buffer[5];
    }

    int16_t getXAccel() { return xAccel; }
    int16_t getYAccel() { return yAccel; }
    int16_t getZAccel() { return zAccel; }
};
