#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string>

class Task {

public:
    Task(std::string name){
        taskName = name;
    };  
    virtual ~Task(){};
    
    static Task * pObjet;

    void start(){
        xTaskCreatePinnedToCore( Task::taskEntry,    "Task wifi",    5000,      this,    2,    NULL,    1);
    };
protected:
    virtual void task() = 0;
private:
    static void taskEntry(void *pvParameters) {
        Task *instance = static_cast<Task *>(pvParameters);
        if (instance) {
            instance->task();
        }
    }
    std::string taskName;
};
