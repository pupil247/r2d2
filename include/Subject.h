#pragma once

#include <set>
#include "Observer.h"
#include <vector>
#include <variant>
#include <string>


class Observer;

enum subject_t {
    WIFI,
    MOTORS,
};

class Subject{
    private:
        std::set<Observer*> observers;
    public:
        Subject(){

        }
        virtual ~Subject() = default;

        virtual subject_t getType() const = 0;

        void attach(Observer * o){
            if(!observers.contains(o)){
                observers.insert(o);
            }
        }
        
        void detach(Observer * o){
            observers.erase(o);
        }

        void notifyObservers();

        virtual void setData(std::vector<std::variant<int, std::string>> data) = 0;
        virtual std::vector<std::variant<int, std::string>> getData() = 0;
};

