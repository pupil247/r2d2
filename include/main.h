#pragma once


//Add dependencies
#include <stdio.h>

//Add custom lib
#include "Movement.h"
#include "Wifi.h"
#include "iomapping.h"

#define pdSecond pdMS_TO_TICKS(1000)

class Main final
{

public:
    ~Main(){
        
    };
    esp_err_t setup(void);
    void loop(void);
private:
    Gpio::GpioOutput led{(gpio_num_t)ioMapping::PIN_LED};
    DAC dac{18};
    Wifi * wifi;
    //i2c i2cInstance{(uint8_t)ioMapping::PIN_SDA,(uint8_t)ioMapping::PIN_SCL,0};
    //lcdI2C screen{i2cInstance, 0x27, 20, 4};
};