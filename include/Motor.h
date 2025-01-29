#pragma once

#include "Observer.h"
#include "Wifi.h"
#include <cmath>
#include <algorithm>

#define MOTOR_ON 1
#define MOTOR_OFF 0
#define PI 3.14159265



class Motor : public Observer{
    public:
        Motor(): Observer(){
            
        }
        void update(Subject * subject) {
            ESP_LOGI("motor","1");
            std::string command = "";
            int direction = 0;
            int intensity = 0;
            int duration = 0;
            ESP_LOGI("motor","2");
            if(subject->getType() == subject_t::WIFI){
                ESP_LOGI("motor","3");
                std::vector<std::variant<int, std::string>> data = ((Wifi*)subject)->getData();
                ESP_LOGI("size",":%d",(int)data.size());
                ESP_LOGI("motor","4");
                command = std::get<std::string>(data[0]);
                ESP_LOGI("motor","5");
                direction = std::get<int>(data[1]);
                ESP_LOGI("motor","6");
                intensity = std::get<int>(data[2]);
                ESP_LOGI("motor","7");
                duration  = 100;
                ESP_LOGI("motor","8");
            }
            if(command == "move"){
                ESP_LOGI("command move","move");
                move(direction, intensity, duration);
            }else if(command == "reset"){

            }else if(command == "stop"){

            }
            ESP_LOGI("motor","6");

        }
        virtual void move(int intensity,int direction, int duration) = 0;
        virtual void stop() = 0;

        
};

