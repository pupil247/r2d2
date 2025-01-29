#pragma once

#include "Subject.h"
#include <cstring>

enum command_t {
    MOTOR_MOVE,
    CMD_RESET,
    CMD_MOVE,
    CMD_STOP,
    DEFAULT
};

class Subject;

class Observer{
    public: 
        Observer(){
            
        }
        virtual void update(Subject * subject) = 0;
        

        static int getCommandType(const char *commandType) {
            if (strcmp(commandType, "reset") == 0) {
                return CMD_RESET;
            } else if (strcmp(commandType, "move") == 0) {
                return CMD_MOVE;
            } else {
                return -1; // Unknown command
            }
        }
};