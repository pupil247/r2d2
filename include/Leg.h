#pragma once

#include "Motor.h"
#include "ioMapping.h"
#include "Gpio.h"
#include <cmath>
#include "dac.h"
#include "Observer.h"

using Gpio::GpioOutput;
using Gpio::GpioInput;

class RightLeg : public Motor{
    private:
        bool isRunning = false;
        bool isStarted = false;

        Gpio::GpioOutput in1{(gpio_num_t)ioMapping::LEGR_IN1};
        Gpio::GpioOutput in2{(gpio_num_t)ioMapping::LEGR_IN2};
        Gpio::GpioOutput standby{(gpio_num_t)ioMapping::LEGR_STNDBY};
        DAC inPWM{(gpio_num_t)ioMapping::LEGR_PWM};
        

    public:
        RightLeg(): Motor(){
            // Configure the pin as an output
            in1.init();
            in2.init();
            inPWM.init();
            standby.init();

            standby.set(Gpio::GpioState::HIGH);
            inPWM.setValue(Gpio::GpioState::LOW);
            in1.set(Gpio::GpioState::LOW);
            in2.set(Gpio::GpioState::LOW);

        }

        virtual void move(int direction, int intensity, int duration){
            printf("right Leg moving\n");


            int speed = intensity * (sin(direction*PI/180) - cos(direction*PI/180));
            setSpeed(speed);
            direction ? forward() : reverse();

            while(duration--){
                ESP_LOGI("leg","leg moving");
                vTaskDelay(pdMS_TO_TICKS(10));
            }
            
            stop();
            
        }

        virtual void stop(){
            printf("Leg braked\n");
            in1.set(Gpio::GpioState::HIGH);
            in2.set(Gpio::GpioState::HIGH);
            inPWM.setValue(0);
            standby.set(Gpio::GpioState::LOW);
        }

        void setSpeed(int speed){
            printf("Leg speed set\n");
            inPWM.setValue(speed);
        }

        void forward(){

            printf("Leg forward\n");
            standby.set(Gpio::GpioState::HIGH);
            in1.set(Gpio::GpioState::HIGH);
            in2.set(Gpio::GpioState::LOW);
            inPWM.setValue(50);
            
        }

        void reverse(){
            printf("Leg reversed\n");
            standby.set(Gpio::GpioState::HIGH);
            in1.set(Gpio::GpioState::LOW);
            in2.set(Gpio::GpioState::HIGH);
            inPWM.setValue(50);
        }

        void brake(){
            printf("Leg braked\n");
            standby.set(Gpio::GpioState::HIGH);
            in1.set(Gpio::GpioState::HIGH);
            in2.set(Gpio::GpioState::HIGH);
            inPWM.setValue(0);
        }

        
       
};

class LeftLeg : public Motor{
    private:
        bool isRunning = false;
        bool isStarted = false;

        Gpio::GpioOutput in1{(gpio_num_t)ioMapping::LEGL_IN1};
        Gpio::GpioOutput in2{(gpio_num_t)ioMapping::LEGL_IN2};
        Gpio::GpioOutput standby{(gpio_num_t)ioMapping::LEGL_STNDBY};
        DAC pwm{ioMapping::LEGL_PWM};

    public:
        LeftLeg(): Motor(){
            // Configure the pin as an output
            //in1.init();
            //in2.init();
            //standby.init();
            //pwm.init();
            
        }

        virtual void move(int direction, int intensity, int duration){
            printf("LEft Leg moving\n");

            int speed = intensity * (sin(direction) + cos(direction));
            setSpeed(speed);
            direction ? forward() : reverse();

            while(duration--){
                
                vTaskDelay(pdMS_TO_TICKS(10));
            }
            stop();
            
        }
        void forward(){
            printf("Leg forward\n");
            in1.set(Gpio::GpioState::HIGH);
            in2.set(Gpio::GpioState::LOW);

            pwm.setValue(75);
            standby.set(Gpio::GpioState::HIGH);
        }

        void reverse(){
            printf("Leg reversed\n");
            in1.set(Gpio::GpioState::LOW);
            in2.set(Gpio::GpioState::HIGH);

            pwm.setValue(75);
            standby.set(Gpio::GpioState::HIGH);
        }

        void setSpeed(int speed){
            printf("Leg speed set\n");
            pwm.setValue(speed);
        }

        

        virtual void stop(){
            printf("Leg braked\n");
            in1.set(Gpio::GpioState::HIGH);
            in2.set(Gpio::GpioState::HIGH);
            pwm.setValue(0);
            standby.set(Gpio::GpioState::LOW);
        }
      
};