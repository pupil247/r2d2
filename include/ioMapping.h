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
    const uint8_t LEGL_IN1 = 20;
    const uint8_t LEGL_IN2 = 21; 
    const uint8_t LEGL_PWM = 19; 
    const uint8_t LEGL_STNDBY = 47;

    //Right Leg pins
    const uint8_t LEGR_IN1 = 48;
    const uint8_t LEGR_IN2 = 35; 
    const uint8_t LEGR_PWM = 36; 
    const uint8_t LEGR_STNDBY = 2;

    const uint8_t sda = 13;
    const uint8_t scl = 14;



};