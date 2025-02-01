/**
 * @file ioMapping.h
 * @author Felix Parent (parent.felix@domain.com)
 * @brief io declarations
 * @version 0.1
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <stdio.h>

namespace ioMapping{

    //Left Leg pins
    const uint8_t LEGR_IN1 = 6;
    const uint8_t LEGR_IN2 = 5; 
    const uint8_t LEGR_PWM = 16; 
    const uint8_t LEGR_STNDBY = 7;

    //Right Leg pins
    const uint8_t LEGL_IN1 = 10;
    const uint8_t LEGL_IN2 = 11; 
    const uint8_t LEGL_PWM = 12; 
    const uint8_t LEGL_STNDBY = 13;

    const uint8_t sda = 8;
    const uint8_t scl = 9;



};