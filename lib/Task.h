#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string>

class Task{

private:
    static Task * pObjet;
    static void task();
public:
    Task(std::string name){
        pObjet = this;
    };  
    ~Task(){};

    void start(){
        xTaskCreatePinnedToCore( (TaskFunction_t)task,    "Task lcd",    5000,      NULL,    2,    NULL,    1);
    };
};


Task* Task::pObjet = nullptr;