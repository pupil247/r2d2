#include "Subject.h"
#include "esp_log.h"

void Subject::notifyObservers(){ //put in cpp file
    ESP_LOGI("observer","1");
    for(Observer * o : observers){
        ESP_LOGI("observer","2");
        o->update(this);
        ESP_LOGI("observer","3");
    }
}