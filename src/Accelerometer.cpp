#pragma once

#include "Accelerometer.h"


Accelerometer::Accelerometer(uint8_t sda, uint8_t scl, i2c_port_t port) {
        i2c_bus = new i2c(sda, scl, port);
}

void Accelerometer::begin() {
    i2c_bus->writeByte((uint8_t)MPU6050_ADDR, (uint8_t)MPU6050_PWR_MGMT_1, (uint8_t)0x00);  // Wake up MPU6050
}

void Accelerometer::readRawAccel() {
    uint8_t buffer[6];
    i2c_bus->readBytes(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, buffer, 6);
    
    xAccel = (buffer[0] << 8) | buffer[1];
    yAccel = (buffer[2] << 8) | buffer[3];
    zAccel = (buffer[4] << 8) | buffer[5];
}

int16_t Accelerometer::getXAccel() { return xAccel; }
int16_t Accelerometer::getYAccel() { return yAccel; }
int16_t Accelerometer::getZAccel() { return zAccel; }