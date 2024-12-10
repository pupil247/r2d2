#include "main.h"
#define LOG_TAG "MAIN"
#include "esp_wifi.h"
#include <esp_mac.h>

static Main my_main;
char data = 0;
uint8_t value = 0;

extern "C" void app_main(void) {

    ESP_ERROR_CHECK(my_main.setup());

    wifi = Wifi::getInstance();
    wifi.start();
    
    while(true)
    {
        my_main.loop();
    }
}

esp_err_t Main::setup(){
    
    esp_err_t status(ESP_OK);
    vTaskDelay(pdMS_TO_TICKS(500));
      
    return status;
}

void Main::loop(){
    ESP_LOGI("Alive","test");
    vTaskDelay(pdSecond); //1s
}